#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "plant.hpp"
#include "sensor.hpp"
#include "pump.hpp"
#include "plant_fsm.hpp"
#include "wifi_handler.hpp"
#include "mqtt_handler.hpp"
#include "secrets.hpp"
#include "config.hpp"

// Use WiFi to handle connections to MQTT broker
WifiHandler wifi;
WiFiClient espClient;
PubSubClient mqttClient(espClient);
MqttHandler mqtt(mqttClient);

Plant plant(Config::SENSOR_PIN, Config::PUMP_PIN);

void ControlTask(void* pvParameters) {
  for (;;) {
    // Confirm connections over WiFi and MQTT
    wifi.maintainConnection( WIFI_SSID, WIFI_PASSWORD );
    mqtt.maintainConnection();

    // Activate pump based on moisture sensor reading
    plant.update();

    // Send sensor reading to MQTT broker
    mqtt.publish( plant.getMoisture() );

    vTaskDelay(Config::CONTROL_TASK_INTERVAL);
  }
}

void setup() {
  Serial.begin(115200);

  // Set up Wi-Fi connection
  wifi.connect( WIFI_SSID, WIFI_PASSWORD );
  mqtt.setup();

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