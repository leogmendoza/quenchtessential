#pragma once

#include <Arduino.h>

#include <mqtt_handler.hpp>

enum class PlantState {
    IDLE,
    DRY,
    WATERING,
    WAITING
};

class PlantFSM {
    public:
        PlantFSM(MqttHandler* mqtt);

        void update(int moisture);
        bool isWatering() const;

    private:
        MqttHandler* mqtt_;
        PlantState state_;
        unsigned long stateStartTime_;

        void transitionTo(PlantState newState);
};