#include "plant.hpp"

Plant::Plant(int sensorPin, int pumpPin, MqttHandler* mqtt) : sensor_(sensorPin), pump_(pumpPin), fsm_(mqtt), lastMoisture_(0) {}

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
