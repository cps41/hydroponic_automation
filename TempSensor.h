#ifndef TempSensor_h
#define TempSensor_h

class TempSensor {
    public:
        TempSensor(int temp_read);
        float getTemp();
    private:
        int _temp_read;
};

#endif