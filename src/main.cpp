#include <Arduino.h>
#include "sensor.hpp"
#include "pump.hpp"

#define GPIO_SENSOR 32
#define GPIO_PUMP 16

struct PlantData {
  int moisture;
};

const TickType_t SENSOR_TASK_INTERVAL = pdMS_TO_TICKS(1000);
const TickType_t CONTROL_TASK_INTERVAL = pdMS_TO_TICKS(500);

const int DRY_THRESHOLD = 3000;  // Temporary; need to actually calibrate

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

    vTaskDelay(SENSOR_TASK_INTERVAL);
  }
  
}

void ControlTask(void* pvParameters) {
  for (;;) {
    if (plantData.moisture < DRY_THRESHOLD) {
      pump.setState(true);
    }
    else {
      pump.setState(false);
    }

    vTaskDelay(CONTROL_TASK_INTERVAL);
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

  xTaskCreate(
    ControlTask, 
    "Control", 
    1024, 
    NULL, 
    1, 
    NULL
  );
}

void loop() {

}