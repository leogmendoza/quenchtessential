#include "sensor.hpp"
#include <Arduino.h>

Sensor::Sensor(int pin) : pin_(pin) {
    pinMode(pin_, INPUT);
}

int Sensor::readMoisture() {
    return analogRead(pin_);
}
