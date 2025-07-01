#if 0

#include <Arduino.h>

#include "pump.hpp"
#include "config.hpp"

#define PUMP_TIME_MS 3500

Pump pump(Config::PUMP_PIN);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("[TEST] Starting pump for test duration...");
  pump.setState(true); // ON
  delay(PUMP_TIME_MS);
  pump.setState(false); // OFF
  Serial.println("[TEST] Pump test complete.");
}

void loop() {
  // Nothing here
}

#endif