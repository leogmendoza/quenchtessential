#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
    public:
        Sensor(int pin);

        int readMoisture();  // TO DO: Implement

    private:
        int pin_;
};

#endif