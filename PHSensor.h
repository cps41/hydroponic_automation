#ifndef PHSensor_h
#define PHSensor_h

#include <Arduino.h>

class PHSensor {
    public:
        PHSensor(int ph_read);
        float getPH();
    private:
        int _ph_read;
};

#endif