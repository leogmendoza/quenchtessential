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
        // Confirm connections over WiFi
        wifi.update();

        // Blink LED when Wi-Fi is not connected
        static unsigned long lastBlink = 0;
        static bool ledState = false;

        WifiState wifiState = wifi.getState();

        if (wifiState != WifiState::CONNECTED) {
            unsigned long now = millis();
            if (now - lastBlink > 500) {
                ledState = !ledState;
                digitalWrite(Config::WIFI_LED_PIN, ledState ? HIGH : LOW);
                lastBlink = now;
            }
        } else {
            digitalWrite(Config::WIFI_LED_PIN, HIGH);
        }

        // Confirm connections over MQTT
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

    // Blink LED when not connected to Wi-Fi
    pinMode(Config::WIFI_LED_PIN, OUTPUT);
    digitalWrite(Config::WIFI_LED_PIN, LOW);

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