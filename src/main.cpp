#include <Arduino.h>
#include "sensor.hpp"
#include "pump.hpp"

#define GPIO_SENSOR 32
#define GPIO_PUMP 16

struct PlantData {
  int moisture;
};

const int DRY_THRESHOLD = 3000;

// Initialize data
PlantData plantData;

// Initialize devices
Sensor sensor(GPIO_SENSOR);
Pump pump(GPIO_PUMP);

void SensorTask(void* pvParameters) {
  for (;;) {
    plantData.moisture = sensor.readMoisture();

    // Testing
    Serial.print("Moisture: ");
    Serial.println(plantData.moisture);

    vTaskDelay( pdMS_TO_TICKS(1000) );
  }
  
}

void setup() {
  Serial.begin(115200);

  xTaskCreate(
    SensorTask, 
    "Sensor", 
    1024, 
    NULL, 
    1, 
    NULL
  );
}

void loop() {
  // Test sensor
  // int moisture = sensor.readMoisture();
  // Serial.print("Moisture: ");
  // Serial.println(moisture);

  // Test pump toggling
  // if (moisture < DRY_THRESHOLD) {
  //   pump.setState(true);
  // }
  // else {
  //   pump.setState(false);
  // }
  
  // delay(1000);
}