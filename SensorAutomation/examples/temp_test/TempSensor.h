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