#pragma once

#include <Arduino.h>

namespace Config {
    constexpr gpio_num_t SENSOR_PIN = GPIO_NUM_32;
    constexpr gpio_num_t PUMP_PIN   = GPIO_NUM_16;

    constexpr TickType_t SENSOR_TASK_INTERVAL  = pdMS_TO_TICKS(1000);
    constexpr TickType_t CONTROL_TASK_INTERVAL = pdMS_TO_TICKS(500);

    constexpr unsigned long WATERING_DURATION_MS = 2000;
    constexpr unsigned long COOLDOWN_DURATION_MS = 2000;

    constexpr unsigned long MQTT_PUBLISH_INTERVAL_MS   = 10000;
    constexpr unsigned long MQTT_RECONNECT_INTERVAL_MS = 5000;

    constexpr const char* MQTT_BROKER    = "test.mosquitto.org";  // Public MQTT broker for testing only
    constexpr const char* MQTT_CLIENT_ID = "plantClient";
    constexpr const char* MQTT_TOPIC     = "quenchtessential/plant/status";
    constexpr int         MQTT_PORT      = 1883;

    constexpr int DRY_THRESHOLD = 3000;  // Temporary; need to actually calibrate!
}