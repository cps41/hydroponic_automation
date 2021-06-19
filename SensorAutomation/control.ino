#include "ec_sensor.ino"
#include "ph_sensor.ino"

const int NUTRIENT_PUMP_PIN = 9;
const float MIN_EC = 1.8;
const float ADJUSTED_EC = 2.4;

void testEC() {
    float EC = getEC();

    if(EC < MIN_EC) {

    }
}
