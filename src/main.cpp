#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "plant.hpp"
#include "sensor.hpp"
#include "pump.hpp"
#include "plant_fsm.hpp"
#include "mqtt_handler.hpp"
#include "secrets.hpp"
#include "config.hpp"

// Use WiFi to handle connections to MQTT broker
WiFiClient espClient;
PubSubClient mqttClient(espClient);
MqttHandler mqtt(mqttClient);

Plant plant(Config::SENSOR_PIN, Config::PUMP_PIN);

void ControlTask(void* pvParameters) {
  for (;;) {
    int moisture;
    static unsigned long lastPublish = 0;

    // Activate pump based on moisture sensor reading
    plant.update();

    mqtt.maintainConnection();
    mqtt.publish(plant.getMoisture());

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