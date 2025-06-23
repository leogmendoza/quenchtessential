#include "plant_fsm.hpp"

const int DRY_THRESHOLD = 3000;  // Temporary; need to actually calibrate
constexpr unsigned long WATERING_DURATION_MS = 2000;
constexpr unsigned long COOLDOWN_DURATION_MS = 2000;

PlantFSM::PlantFSM(): state_(PlantState::IDLE), stateStartTime_(millis()) {}

void PlantFSM::update(int moisture) {
    switch (state_) {
        case (PlantState::IDLE):
            if (moisture < DRY_THRESHOLD) {
                transitionTo(PlantState::DRY);
            }
            break;

        case (PlantState::DRY):
            transitionTo(PlantState::WATERING);
            break;

        case (PlantState::WATERING):
            if (millis() - stateStartTime_ > WATERING_DURATION_MS) {
                transitionTo(PlantState::WAITING);
            }
            break;

        case (PlantState::WAITING):
            if (millis() - stateStartTime_ > COOLDOWN_DURATION_MS) {
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
}