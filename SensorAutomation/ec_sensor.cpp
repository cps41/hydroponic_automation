/* 
EC Sensor Automation
Author: Carly Sills
*/
#include <ECSensor.h>
#include <TempSensor.h>
#include <INA260Sensor.h>
#include <Arduino.h>

const float A = 0.20; // area of electrodes
const float L = 0.75; // distance between electrodes
const float TEMP_REG = 25.0; // ec is regulated based on temp of 25 deg celcius
const float EC_CALIB = 2000; // TBD
const int READ_DELAY = 5000;
const float TEMP_CO = 0.019;

float G; // conductance
float R; // resistance
float U; // potential
float I; // current
float K = L/A; // cell constant
float k; // actual conductance

ECSensor::ECSensor(int ec_power, int temp_read, int temp_power) {
    // instantiate EC sensor
    _ec_power = ec_power;
    _temp_read = temp_read;
    _temp_power = temp_power;
    ina_current = INA260Sensor(0x40);
    ina_voltage = INA260Sensor(0x44);
}

/*
    Function to read value from EC sensor and convert it to usable data

    return: EC: (float) conductivity detected by sensor
*/
float ECSensor::getEC() {
    float temp;
    float EC;
    float EC_uncalibrated;
    TempSensor temp_sensor(_temp_read, _temp_power);

    digitalWrite(_ec_power, HIGH); // power sensor
    U += ina_voltage.getVoltage();
    I += ina_current.getCurrent();
    temp = temp_sensor.getTemp();
    R = U/I;
    digitalWrite(_ec_power, LOW); // shutdown sensor

    EC_uncalibrated = 1000/(R*K); // EC = 1000/(resistance*cell constant)
    EC = EC_uncalibrated*1000 / (1+TEMP_CO*(temp-TEMP_REG)); // calculate against temp calibration

    Serial.print(" EC: ");
    Serial.print(EC);
    Serial.println(" microSiemens/cm");
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.println(" *C");
}

/*
    Function to calibrate EC sensor and calculate calibration coefficient
*/
void ECSensor::ecCalibrate () {
    float temp_start, temp_end, temp_dif;
    float EC;
    float K_cal;
    TempSensor temp_sensor(_temp_read, _temp_power);
    INA260Sensor ina_current(0x40);
    INA260Sensor ina_voltage(0x44);

    Serial.println("Calibration routine started");
    digitalWrite(_ec_power, HIGH); // power sensor

    temp_start = temp_sensor.getTemp(); // get initial temp

    // get average voltage and current across sample size of n
    for(int i=0; i<10; i++) {
        U += ina_voltage.getVoltage();
        I += ina_current.getCurrent();
        delay(READ_DELAY);
    }

    temp_end = temp_sensor.getTemp(); // get final temp
    // calculate averages
    U /= 10;
    I /= 10;

    temp_dif = temp_start-temp_end;

    R = U/I; // R = U/I (ohms law)

    // avgResistance(temp_sensor, ina260_sensor);
    digitalWrite(_ec_power, LOW); // shutdown sensor

    EC = EC_CALIB / (1+TEMP_CO*(temp_end-TEMP_REG)); // Calibrated EC = EC_25/(1 + α(t-25))
    K_cal= 1000/(R*EC);

    Serial.print("EC: ");
    Serial.print(EC);
    Serial.print("\n");

    Serial.print("Cell constant was ");
    Serial.print(K);
    Serial.print(", is now ");
    Serial.println(K_cal);

    K = K_cal;

    Serial.print("Temperature difference start to end were = ");
    Serial.print(temp_dif);
    Serial.println("*C");
    if(temp_dif >= 0.15) {
        Serial.println("Temperature difference start to end must be smaller than 0.15*C, restarting");
        Serial.println("");
        ecCalibrate();
    }
}
