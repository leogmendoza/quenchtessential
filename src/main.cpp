#include <Arduino.h>
#include "sensor.hpp"
#include "pump.hpp"

#define GPIO_A 6
#define GPIO_B 7

// Initialize devices
Sensor sensor_A(GPIO_A);
Pump pump_A(GPIO_B);

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Test sensor
  int moisture_A = sensor_A.readMoisture();
  Serial.print("Moisture: ");
  Serial.println(moisture_A);

  // Test pump toggling
  pump_A.setState(true);
  delay(500);
  pump_A.setState(false);
  delay(500);
}