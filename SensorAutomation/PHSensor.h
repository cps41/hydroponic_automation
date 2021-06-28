#ifndef PHSensor_h
#define PHSensor_h

#include <Arduino.h>

class PHSensor {
    public:
        PHSensor(int ph_read, int ph_power);
        float getPH();
    private:
        int _ph_read;
        int _ph_power;
};

#endif