#include "sensor.hpp"

#include <Arduino.h>
#include <config.hpp>

Sensor::Sensor(int pin) : pin_(pin) {
    pinMode(pin_, INPUT);
}

int Sensor::readMoisture() {
    int raw = analogRead(pin_);
    int percent = map(raw, PLANT_DRY_THRESHOLD_RAW, PLANT_WET_THRESHOLD_RAW, 0, 100);

    return constrain(percent, 0, 100);
}
