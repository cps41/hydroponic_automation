#ifndef INA260Sensor_h
#define INA260Sensor_h

class INA260Sensor {
    public:
        INA260Sensor(int ina_read, int ina_power);
        float getCurrent();
        float getVoltage();
        float getPower();
    private:
        int _ina_read;
        int _ina_power;
};

#endif