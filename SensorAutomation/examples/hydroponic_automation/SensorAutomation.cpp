#include "SensorAutomation.h"
#include <Arduino.h>
#include "ECSensor.h"
#include "PHSensor.h"
#include "INA260Sensor.h"
#include "TempSensor.h"

const float MIN_EC = 1.2;
const float REG_EC = 1.8;
const float MIN_PH = 5.5;
const float MAX_PH = 7.5;
const float REG_PH = 6;

SensorAutomation::SensorAutomation(int ec_power, 
                         int ph_read, int ph_power, 
                         int temp_read, int temp_power, 
                         int up_pump, int down_pump, int nutrient_pump) {
    _ec_power = ec_power;
    _ph_read = ph_read;
    _ph_power = ph_power;
    _temp_read = temp_read;
    _temp_power = temp_power;
    _up_pump = up_pump;
    _down_pump = down_pump;
    _nutrient_pump = nutrient_pump;
}

void SensorAutomation::calibrateEC() {
    ECSensor ec_sensor(_ec_power, _temp_read, _temp_power);
    ec_sensor.ecCalibrate();
}

void SensorAutomation::checkEC() {
    float EC;
    Serial.print("Getting EC...\n");
    ECSensor ec_sensor(_ec_power, _temp_read, _temp_power);
    EC = ec_sensor.getEC();

    if(EC < MIN_EC) regulateEC();
}

void SensorAutomation::regulateEC() {
    float EC;
    ECSensor ec_sensor(_ec_power, _temp_read, _temp_power);
    EC = ec_sensor.getEC();

    if(EC < REG_EC) {
        digitalWrite(_nutrient_pump, HIGH);
        delay(5000);
        regulateEC();
    }
    else digitalWrite(_nutrient_pump, LOW);
}

void SensorAutomation::checkPH() {
    float PH;
    PHSensor ph_sensor(_ph_read, _ph_power);
    PH = ph_sensor.getPH();

    if(PH < MIN_PH) upPH();
    else if(PH>MAX_PH) downPH();
}

void SensorAutomation::upPH() {
    float PH;
    PHSensor ph_sensor(_ph_read, _ph_power);
    PH = ph_sensor.getPH();

    if(PH < REG_PH) {
        digitalWrite(_up_pump, HIGH);
        delay(5000);
        upPH();
    }
    else digitalWrite(_up_pump, LOW);
}

void SensorAutomation::downPH() {
    float PH;
    PHSensor ph_sensor(_ph_read, _ph_power);
    PH = ph_sensor.getPH();

    if(PH > REG_PH) {
        digitalWrite(_down_pump, HIGH);
        delay(5000);
        upPH();
    }
    else digitalWrite(_down_pump, LOW);
}