/*
    SensorAutomation.h - Library for hydroponic sensor automation
    Created by Carly Sills, June 19, 2021.
    Use is for ECE1896 only.
*/

#ifndef SensorAutomation_h
#define SensorAutomation_h

class SensorAutomation {
    public:
        SensorAutomation(int ec_read, int ec_power, 
                         int ph_read, int ph_power, 
                         int temp_read, int temp_power, 
                         int ina_read, int ina_power,
                         int up_pump, int down_pump, int nutrient_pump);
        void calibrateEC();
        void checkEC();
        void checkPH();
    private:
        int _ec_read;
        int _ec_power;
        int _ph_read;
        int _ph_power;
        int _temp_read;
        int _temp_power;
        int _ina_read;
        int _ina_power;
        int _up_pump;
        int _down_pump;
        int _nutrient_pump;
        void regulateEC();
        void upPH();
        void downPH();
};

#endif

#ifndef ECSensor_h
#define ECSensor_h

class ECSensor {
    public:
        ECSensor(int ec_read, int ec_power,
                         int temp_read, int temp_power, 
                         int ina_read, int ina_power);
        void ecCalibrate();
        float getEC();
    private:
        int _ec_read;
        int _ec_power;
        int _temp_read;
        int _temp_power;
        int _ina_read;
        int _ina_power;
};

#endif

#ifndef TempSensor_h
#define TempSensor_h

class TempSensor {
    public:
        TempSensor(int temp_read, int temp_power);
        float getTemp();
    private:
        int _temp_read;
        int _temp_power;
};

#endif

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

#ifndef PHSensor_h
#define PHSensor_h

class PHSensor {
    public:
        PHSensor(int ph_read, int ph_power);
        float getPH();
    private:
        int _ph_read;
        int _ph_power;
};

#endif