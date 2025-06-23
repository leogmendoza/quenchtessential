#pragma once

class Pump {
    public:
        Pump(int pin);
        void setState(bool on);  // TODO: Implement

    private:
        int pin_;
};