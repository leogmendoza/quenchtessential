#include "pump.hpp"
#include <Arduino.h>

Pump::Pump(int pin) : pin_(pin) {
    // TODO: Set pinMode
}

void Pump::setState(bool on) {
    Serial.print("Pump is now ");
    Serial.println(on ? "ON" : "OFF");
}
