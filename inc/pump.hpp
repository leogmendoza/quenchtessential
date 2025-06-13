#ifndef PUMP_H
#define PUMP_H

class Pump {
    public:
        Pump(int pin);
        void setState(bool on);  // TODO: Implement

    private:
        int pin_;
};

#endif