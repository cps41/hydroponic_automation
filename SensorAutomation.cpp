#include "SensorAutomation.h"
#include "ECSensor.h"
#include "PHSensor.h"
#include "INA260Sensor.h"
#include "TempSensor.h"
#include <Arduino.h>

const float MIN_EC = 1200;
const float REG_EC = 1400;
const float MIN_PH = 5.5;
const float MAX_PH = 7.5;
const float REG_PH = 7;

SensorAutomation::SensorAutomation(int ec_analog, int ph_read, int temp_read,
                         int up_pump, int down_pump, int nutrient_pump) {
    _ec_analog = ec_analog;
    _ph_read = ph_read;
    _temp_read = temp_read;
    _up_pump = up_pump;
    _down_pump = down_pump;
    _nutrient_pump = nutrient_pump;
}

// Calibrate EC sensor
void SensorAutomation::calibrateEC() {
   ECSensor ec_sensor(A0, _temp_read);
   ec_sensor.ecCalibrate();
}

// Check EC, begin regulation process if below threshold
void SensorAutomation::checkEC() {
    float res_EC;
    Serial.println("Getting EC...");
    ECSensor ec_sensor(A0, _temp_read);
    res_EC = ec_sensor.get_ec_tds();


    // Pump nutrients into solution until reaching regulation EC level
    if(res_EC < MIN_EC) {
        Serial.println("Regulating EC...");
        while(res_EC < REG_EC) {
            digitalWrite(_nutrient_pump, HIGH); // Trigger pump
            delay(500);
            digitalWrite(_nutrient_pump, LOW); // Turn pump off
            delay(2000);
            res_EC = ec_sensor.get_ec_tds();
        }
    }
}

// Check pH, begin pH up sequence if balance is too low, or pH down sequence if balance is too high
void SensorAutomation::checkPH() {
    Serial.println("Getting pH...");
    float res_ph;
    PHSensor ph_sensor(_ph_read);
    res_ph = ph_sensor.getPH();

    if(res_ph < MIN_PH) {
        Serial.println("Pumping pH Up...");
        delay(500);    
        upPH();
    }
    else if(res_ph>MAX_PH) {
        Serial.println("Pumping pH Down...");
        delay(500);    
        downPH();
    }
}

// Pump pH Up into solution until reaching regulation pH
void SensorAutomation::upPH() {
    float res_ph;
    PHSensor ph_sensor(_ph_read);
    res_ph = ph_sensor.getPH();

    if(res_ph < REG_PH) {
        digitalWrite(_up_pump, HIGH); // Trigger pump
        delay(2000);
//        delay(500);
        digitalWrite(_up_pump, LOW); // Turn pump off
        delay(500);
//        delay(2000);
        upPH();
    }
}

// Pump pH Down into solution until reaching regulation pH
void SensorAutomation::downPH() {
    float res_ph;
    PHSensor ph_sensor(_ph_read);
    res_ph = ph_sensor.getPH();

    if(res_ph > REG_PH) {
        digitalWrite(_down_pump, HIGH); // Trigger pump
        delay(2000);
        //delay(500);
        digitalWrite(_down_pump, LOW); // Turn pump off
        delay(500);
        //delay(2000);
        downPH();
    }
}
