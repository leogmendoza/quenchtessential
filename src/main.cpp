#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "plant.hpp"
#include "sensor.hpp"
#include "pump.hpp"
#include "plant_fsm.hpp"
#include "wifi_manager_fsm.hpp"
#include "mqtt_handler.hpp"
#include "config.hpp"

// Use WiFi to handle connections to MQTT broker
WifiManagerFSM wifi;
WiFiClient espClient;
PubSubClient mqttClient(espClient);
MqttHandler mqtt(mqttClient);

Plant plant( Config::SENSOR_PIN, Config::PUMP_PIN, &mqtt );

void ControlTask(void* pvParameters) {
    for (;;) {
        // Confirm connections over WiFi and MQTT
        wifi.update();
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

    wifi.begin();

    // Set up Wi-Fi connection
    if ( wifi.getState() == WifiState::FAILED ) {
        Serial.println("[System] Wi-Fi setup failed. Restarting ESP32 . . . ");
        delay(3000);

        ESP.restart();
    }

    // Set up MQTT connection
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