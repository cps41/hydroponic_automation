#ifndef INA260Sensor_h
#define INA260Sensor_h

#include <Adafruit_INA260.h>

class INA260Sensor {
    public:
        INA260Sensor(uint8_t addr=INA260_I2CADDR_DEFAULT);
        float getCurrent();
        float getVoltage();
        float getPower();
    private:
        Adafruit_INA260 ina260;
};

#endif
