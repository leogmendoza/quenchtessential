#pragma once

class Sensor {
    public:
        Sensor(int pin);

        int readMoisture();  // TO DO: Implement

    private:
        int pin_;
};