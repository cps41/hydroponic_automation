/*
    SensorAutomation.h - Library for hydroponic sensor automation
    Created by Carly Sills, June 19, 2021.
    Use is for ECE1896 only.
*/

#ifndef SensorAutomation_h
#define SensorAutomation_h

class SensorAutomation {
    public:
        SensorAutomation(int ec_power, 
                         int ph_read, int ph_power, 
                         int temp_read, int temp_power,
                         int up_pump, int down_pump, int nutrient_pump);
        void calibrateEC();
        void checkEC();
        void checkPH();
    private:
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
