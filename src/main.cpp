#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "sensor.hpp"
#include "pump.hpp"
#include "plant_fsm.hpp"
#include "secrets.hpp"

#define GPIO_SENSOR 32
#define GPIO_PUMP 16

const char* MQTT_BROKER = "test.mosquitto.org";  // Public MQTT broker for testing only
const int MQTT_PORT = 1883;
const char* MQTT_CLIENT_ID = "plantClient";

const TickType_t SENSOR_TASK_INTERVAL = pdMS_TO_TICKS(1000);
const TickType_t CONTROL_TASK_INTERVAL = pdMS_TO_TICKS(500);

PlantFSM plantFsm;

// Use WiFi to handle connections to MQTT broker
WiFiClient espClient;
PubSubClient mqttClient(espClient);

QueueHandle_t moistureQueue;

const int DRY_THRESHOLD = 3000;  // Temporary; need to actually calibrate

// Initialize devices
Sensor sensor(GPIO_SENSOR);
Pump pump(GPIO_PUMP);

void SensorTask(void* pvParameters) {
  for (;;) {
    // Take moisture measurement and prepare for control logic
    int moisture = sensor.readMoisture();
    xQueueSend( moistureQueue, &moisture, portMAX_DELAY );

    Serial.print("Moisture: ");
    Serial.println(moisture);

    vTaskDelay(SENSOR_TASK_INTERVAL);
  } 
}

void ControlTask(void* pvParameters) {
  for (;;) {
    int moisture;

    if ( xQueueReceive( moistureQueue, &moisture, 0 ) == pdTRUE ) {
      // Activate pump based on moisture sensor reading
      plantFsm.update(moisture);
      pump.setState(plantFsm.isWatering());
    }

    vTaskDelay(CONTROL_TASK_INTERVAL);
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

  // Set up MQTT
  mqttClient.setServer( MQTT_BROKER, MQTT_PORT );

  if ( mqttClient.connect(MQTT_CLIENT_ID) ) {
    Serial.println("MQTT connected!");
  } else {
    Serial.print("MQTT failed . . . State: ");
    Serial.println( mqttClient.state() );
  }

  // Set up sensor data queue
  moistureQueue = xQueueCreate( 5, sizeof(int) );

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
    1024, 
    NULL, 
    1, 
    NULL
  );
}

void loop() {

}