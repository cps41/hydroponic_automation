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