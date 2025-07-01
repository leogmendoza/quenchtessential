#pragma once

#include <Arduino.h>

namespace Config {
    constexpr int WIFI_LED_PIN = 2;  // Onboard LED

    constexpr gpio_num_t SENSOR_PIN = GPIO_NUM_32;
    constexpr gpio_num_t PUMP_PIN   = GPIO_NUM_14;

    constexpr TickType_t SENSOR_TASK_INTERVAL  = pdMS_TO_TICKS(1000);   // Deprecated
    constexpr TickType_t CONTROL_TASK_INTERVAL = pdMS_TO_TICKS(500);

    constexpr unsigned long WATERING_DURATION_MS = 3500;    // Time to pump ~100 mL of water (x1 per week frequency)
    constexpr unsigned long COOLDOWN_DURATION_MS = 10000;

    constexpr unsigned long WIFI_RECONNECT_INTERVAL_MS = 5000;
    constexpr unsigned long MQTT_PUBLISH_INTERVAL_MS   = 10000;
    constexpr unsigned long MQTT_RECONNECT_INTERVAL_MS = 5000;

    constexpr const char* MQTT_BROKER    = "test.mosquitto.org";  // Public MQTT broker for testing only
    constexpr const char* MQTT_CLIENT_ID = "plantClient";
    constexpr const char* MQTT_TOPIC     = "quenchtessential/plant/status";
    constexpr int         MQTT_PORT      = 1883;

    // Used to arbitrarily set absolute thresholds
    constexpr int PLANT_DRY_THRESHOLD_RAW = 3200;     // No water for 1 week
    constexpr int PLANT_WET_THRESHOLD_RAW = 2775;     // Watered with 1 cup

    // Arbitrary thresholds
    constexpr int PLANT_ABSOLUTE_DRY_THRESHOLD_RAW = 3250;     // "Lower" bound for percentage
    constexpr int PLANT_ABSOLUTE_WET_THRESHOLD_RAW = 2625;     // "Upper" bound for percentage

    // Actual raw moisture value used when determining when to water
    constexpr int PLANT_THIRSTY_THRESHOLD_RAW = 3000;      // Aiming for watering twice a week with half the weekly dose (100 mL every 2 days)
    constexpr int PLANT_THIRSTY_THRESHOLD_PERCENT = 40;    // = [ 100 * (3250 - 3000) ] / (3250 - 2625) 

    // Mostly for reference
    constexpr int SENSOR_DRY_RAW = 1650;  // Sensor completely submerged in water (minimum)
    constexpr int SENSOR_WET_RAW = 3450;  // Sensor sitting dry in air (maximum)
}