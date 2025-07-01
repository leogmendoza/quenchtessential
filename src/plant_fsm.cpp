#include "plant_fsm.hpp"

#include <Arduino.h>
#include "config.hpp"

PlantFSM::PlantFSM(MqttHandler* mqtt): mqtt_(mqtt), state_(PlantState::IDLE), stateStartTime_(millis()) {}

void PlantFSM::update(int moisture) {
    switch (state_) {
        case (PlantState::IDLE):
            if (moisture < Config::PLANT_THIRSTY_THRESHOLD_PERCENT) {
                transitionTo(PlantState::DRY);
            }
            break;

        case (PlantState::DRY):
            transitionTo(PlantState::WATERING);
            break;

        case (PlantState::WATERING):
            if (millis() - stateStartTime_ > Config::WATERING_DURATION_MS) {
                transitionTo(PlantState::WAITING);
            }
            break;

        case (PlantState::WAITING):
            if (millis() - stateStartTime_ > Config::COOLDOWN_DURATION_MS) {
                transitionTo(PlantState::IDLE);
            }
            break;
    }
}

bool PlantFSM::isWatering() const {
    return (state_ == PlantState::WATERING);
}

void PlantFSM::transitionTo(PlantState newState) {
    state_ = newState;
    stateStartTime_ = millis();

    if (newState == PlantState::WATERING && mqtt_) {
        mqtt_->publishWateredEvent();
    }
}