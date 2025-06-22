#include "pump.hpp"
#include <Arduino.h>

Pump::Pump(int pin) : pin_(pin) {
    pinMode(pin_, OUTPUT);
    digitalWrite(pin_, LOW);
}

void Pump::setState(bool on) {
    // Note: Pump is active-low
    digitalWrite(pin_, on ? LOW : HIGH);
}
