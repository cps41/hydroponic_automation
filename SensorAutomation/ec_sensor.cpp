/* 
EC Sensor Automation
Author: Carly Sills
*/
#include <ECSensor.h>
#include <TempSensor.h>
#include <INA260Sensor.h>
#include <Arduino.h>

const float A = 10; // area of electrodes
const float L = 1; // distance between electrodes
const float TEMP_REG = 25.0; // ec is regulated based on temp of 25 deg celcius
const float EC_CALIB = 1; // TBD
const int READ_DELAY = 5000;
const float TEMP_CO = 0.019;

float G; // conductance
float R; // resistance
float U; // potential
float I; // current
float K = L/A; // cell constant
float k; // actual conductance

float info[] = {0, 0, 0};

void * avgResistance(TempSensor temp_sensor, INA260Sensor ina260_sensor) {
    float temp_start, temp_end;
    float avg_v = 0;
    float avg_i = 0;
    float temp;
    float R_Water;
    float temp_dif;
    float V_init = 5;

    temp_start = temp_sensor.getTemp(); // get initial temp

    // get average voltage and current across sample size of n
    for(int i=0; i<10; i++) {
        avg_v += ina260_sensor.getVoltage();
        avg_i += ina260_sensor.getCurrent();
        delay(READ_DELAY);
    }

    temp_end = temp_sensor.getTemp(); // get final temp
    // calculate averages
    U = avg_v/10;
    I = avg_i/10;

    temp_dif = temp_start-temp_end;
    temp = (temp_start+temp_end)/2;

    R = U/I; // R = U/I (ohms law)
    info[0] = R;
    info[1] = temp_start;
    info[2] = temp_end;
}

ECSensor::ECSensor(int ec_read, int ec_power,
                    int temp_read, int temp_power, 
                    int ina_read, int ina_power) {
    // instantiate EC sensor
    _ec_read = ec_read;
    _ec_power = ec_power;
    _temp_read = temp_read;
    _temp_power = temp_power;
    _ina_read = ina_read;
    _ina_power = ina_power;
}

/*
    Function to read value from EC sensor and convert it to usable data

    return: EC: (float) conductivity detected by sensor
*/
float ECSensor::getEC() {
    float avg_ec_voltage;
    float temp;
    float EC;
    float EC_uncalibrated;
    float V_init = 5;
    float V_in = 0;
    float R_Water = 0;
    TempSensor temp_sensor(_temp_read, _temp_power);
    INA260Sensor ina260_sensor(_ina_read, _ina_power);

    digitalWrite(_ec_power, HIGH); // power sensor
    U += ina260_sensor.getVoltage();
    I += ina260_sensor.getCurrent();
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
    INA260Sensor ina260_sensor(_ina_read, _ina_power);

    Serial.println("Calibration routine started");
    digitalWrite(_ec_power, HIGH); // power sensor
    avgResistance(temp_sensor, ina260_sensor);
    digitalWrite(_ec_power, LOW); // shutdown sensor

    R = info[0]; // averages[0] = average resistance
    temp_start = info[1]; // averages[1] = initial temp
    temp_end = info[2]; // averages[2] = final temp
    temp_dif = temp_end - temp_start;

    EC = EC_CALIB / (1+TEMP_CO*(temp_end-TEMP_REG)); // Calibrated EC = EC_25/(1 + α(t-25))
    K_cal= 1000/(R*EC);

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
