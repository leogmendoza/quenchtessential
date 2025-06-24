#pragma once

#include "sensor.hpp"
#include "pump.hpp"
#include "plant_fsm.hpp"

class Plant {
    public:
        Plant( int sensorPin, int pumpPin );

        void update();
        int getMoisture() const;
        bool isWatering() const;

    private:
        Sensor sensor_;
        Pump pump_;
        PlantFSM fsm_;
        int lastMoisture_;
};
