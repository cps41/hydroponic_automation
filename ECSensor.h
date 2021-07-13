#ifndef ECSensor_h
#define ECSensor_h

#include "INA260Sensor.h"

class ECSensor {
    public:
        ECSensor(int ec_power, int temp_read);
        float ecCalibrate();
        float getEC(float K);
        float get_ec_tds();
    private:
        int _ec_power;
        int _temp_read;
        int _temp_power;
        INA260Sensor ina_current;
        INA260Sensor ina_voltage;
};

#endif
