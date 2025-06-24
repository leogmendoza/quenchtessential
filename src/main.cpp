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

const int DRY_THRESHOLD = 3000;  

// Initialize devices
Sensor sensor(Config::SENSOR_PIN);
Pump pump(Config::PUMP_PIN);

void ensureMqttConnection() {
  static unsigned long lastReconnectAttempt = 0;
  unsigned long now = millis(); 

  // Guard for MQTT reconnection with throttling to prevent repeated failures
  if ( ( !mqttClient.connected() ) && ( ( now - lastReconnectAttempt ) > Config::MQTT_RECONNECT_INTERVAL_MS ) ) {
    Serial.println("MQTT disconnected, attempting to reconnect . . .");
    lastReconnectAttempt = now;

    if ( mqttClient.connect(Config::MQTT_CLIENT_ID) ) {
      Serial.println("MQTT reconnected!");
    } else {
      Serial.print("MQTT reconnect failed. State: ");
      Serial.println( mqttClient.state() );
    }
  }
}

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

    ensureMqttConnection();

    if ( ( mqttClient.connected() ) && ( ( millis() - lastPublish ) > Config::MQTT_PUBLISH_INTERVAL_MS ) ) {
      char payload[64];

      // Format moisture reading string into payload buffer
      snprintf( payload, sizeof(payload), "{\"moisture\": %d}", moisture );

      // Test payload formatting
      Serial.println(payload);

      mqttClient.publish( Config::MQTT_TOPIC, payload );

      lastPublish = millis();
    }

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

  // Set up MQTT
  mqttClient.setServer( Config::MQTT_BROKER, Config::MQTT_PORT );

  if ( mqttClient.connect(Config::MQTT_CLIENT_ID) ) {
    Serial.println("MQTT connected!");
  } else {
    Serial.print("MQTT failed . . . State: ");
    Serial.println( mqttClient.state() );
  }

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