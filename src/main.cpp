#include <Arduino.h>
#include "sensor.hpp"
#include "pump.hpp"

#define GPIO_A 32
#define GPIO_B 16

const int DRY_THRESHOLD = 3000;

// Initialize devices
Sensor sensor(GPIO_A);
Pump pump(GPIO_B);

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Test sensor
  int moisture = sensor.readMoisture();
  Serial.print("Moisture: ");
  Serial.println(moisture);

  // Test pump toggling
  if (moisture < DRY_THRESHOLD) {
    pump.setState(true);
  }
  else {
    pump.setState(false);
  }
  
  delay(1000);
}