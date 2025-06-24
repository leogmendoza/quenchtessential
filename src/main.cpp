#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "sensor.hpp"
#include "pump.hpp"
#include "plant_fsm.hpp"
#include "mqtt_handler.hpp"
#include "secrets.hpp"
#include "config.hpp"

PlantFSM plantFsm;

// Use WiFi to handle connections to MQTT broker
WiFiClient espClient;
PubSubClient mqttClient(espClient);
MqttHandler mqtt(mqttClient);

QueueHandle_t moistureQueue;

// Initialize devices
Sensor sensor(Config::SENSOR_PIN);
Pump pump(Config::PUMP_PIN);

void SensorTask(void* pvParameters) {
  for (;;) {
    // Take moisture measurement and prepare for control logic
    int moisture = sensor.readMoisture();

    // Avoid blocking when queue is full
    if ( xQueueSend( moistureQueue, &moisture, 0 ) != pdPASS ) {
      Serial.println("Queue full, so skipping moisture value :o");
    }


    Serial.print("Moisture: ");
    Serial.println(moisture);

    vTaskDelay(Config::SENSOR_TASK_INTERVAL);
  } 
}

void ControlTask(void* pvParameters) {
  for (;;) {
    int moisture;
    static unsigned long lastPublish = 0;

    if ( xQueueReceive( moistureQueue, &moisture, 0 ) == pdTRUE ) {
      // Activate pump based on moisture sensor reading
      plantFsm.update(moisture);
      pump.setState(plantFsm.isWatering());
    }

    mqtt.maintainConnection();
    mqtt.publish(moisture);

    vTaskDelay(Config::CONTROL_TASK_INTERVAL);
  }
}

void setup() {
  Serial.begin(115200);

  // Set up Wi-Fi connection
  WiFi.begin( WIFI_SSID, WIFI_PASSWORD );
  Serial.print("Beaming it up to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(" .");

    delay(500);
  }

  Serial.println();
  Serial.println("Wi-Fi is beamed up!");
  Serial.print("IP Address: ");
  Serial.println( WiFi.localIP() );

  mqtt.setup();

  // Set up sensor data queue
  moistureQueue = xQueueCreate( 10, sizeof(int) );

  if (moistureQueue == NULL) {
    Serial.println("Moisture queue couldn't be created! :(");
  }

  // Set up tasks
  xTaskCreate(
    SensorTask, 
    "Sensor", 
    1024, 
    NULL, 
    1, 
    NULL
  );

  xTaskCreate(
    ControlTask, 
    "Control", 
    4096, 
    NULL, 
    1, 
    NULL
  );
}

void loop() {

}