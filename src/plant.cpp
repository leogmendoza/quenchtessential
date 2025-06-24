#include "plant.hpp"

Plant::Plant( int sensorPin, int pumpPin ): sensor_(sensorPin), pump_(pumpPin), lastMoisture_(0) {}

void Plant::update() {
    lastMoisture_ = sensor_.readMoisture();
    fsm_.update(lastMoisture_);
    pump_.setState( fsm_.isWatering() );
}

int Plant::getMoisture() const {
    return lastMoisture_;
}

bool Plant::isWatering() const {
    return fsm_.isWatering(); 
}
