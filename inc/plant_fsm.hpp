#pragma once

#include <Arduino.h>

enum class PlantState {
    IDLE,
    DRY,
    WATERING,
    WAITING
};

class PlantFSM {
    public:
        PlantFSM();

        void update(int moisture);
        bool isWatering() const;

    private:
        PlantState state_;
        unsigned long stateStartTime_;

        void transitionTo(PlantState newState);
}