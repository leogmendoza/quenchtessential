#include <Arduino.h>
#include "sensor.hpp"
#include "pump.hpp"
#include "plant_fsm.hpp"

#define GPIO_SENSOR 32
#define GPIO_PUMP 16

PlantFSM plantFsm;

QueueHandle_t moistureQueue;

const TickType_t SENSOR_TASK_INTERVAL = pdMS_TO_TICKS(1000);
const TickType_t CONTROL_TASK_INTERVAL = pdMS_TO_TICKS(500);

const int DRY_THRESHOLD = 3000;  // Temporary; need to actually calibrate

// Initialize devices
Sensor sensor(GPIO_SENSOR);
Pump pump(GPIO_PUMP);

void SensorTask(void* pvParameters) {
  for (;;) {
    // Take moisture measurement and prepare for control logic
    int moisture = sensor.readMoisture();
    xQueueSend( moistureQueue, &moisture, portMAX_DELAY );

    Serial.print("Moisture: ");
    Serial.println(moisture);

    vTaskDelay(SENSOR_TASK_INTERVAL);
  } 
}

void ControlTask(void* pvParameters) {
  for (;;) {
    int moisture;

    if ( xQueueReceive( moistureQueue, &moisture, 0 ) == pdTRUE ) {
      // Activate pump based on moisture sensor reading
      plantFsm.update(moisture);
      pump.setState(plantFsm.isWatering());
    }

    vTaskDelay(CONTROL_TASK_INTERVAL);
  }
}

void setup() {
  Serial.begin(115200);

  moistureQueue = xQueueCreate( 5, sizeof(int) );

  if (moistureQueue == NULL) {
    Serial.println("Moisture queue couldn't be created! :(");
  }

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