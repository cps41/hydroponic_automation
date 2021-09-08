/* 
EC Sensor Automation
Author: Carly Sills
*/
#include "ECSensor.h"
#include "TempSensor.h"
#include "INA260Sensor.h"
#include <Arduino.h>

const float TEMP_REG = 25.0; // ec is regulated based on temp of 25 deg celcius
const float EC_CALIB = 1500; // ec level of calibration solution
const float TEMP_CO = 0.019;

static float Offset = 0.00 ;
const int ArrayLength = 40; // samples
int EC_Buf[ArrayLength]; // Store the average value of the sensor feedback
float temp_reg = 1.0;

ECSensor::ECSensor(int ec_power, int temp_read) {
    // instantiate EC sensor
    _ec_power = ec_power;
    _temp_read = temp_read;
}

/*
    Function to calibrate EC sensor and calculate calibration coefficient
*/
float ECSensor::ecCalibrate () {
    Serial.println("Calibration routine started");
    float temp_start, temp_end, temp_dif;
    float EC;
    TempSensor temp_sensor(_temp_read);
    
    temp_start = temp_sensor.getTemp(); // get initial temp
    EC = get_ec_tds();
    temp_end = temp_sensor.getTemp(); // get final temp
    
    temp_dif = temp_start-temp_end;

    Serial.print("EC: ");
    Serial.println(EC);

    Serial.print("Offset was ");
    Serial.print(Offset);
    Serial.print(", is now ");
    Offset = EC_CALIB-EC; // set offset for calibration based on difference between expected and actual readings
    Serial.println(Offset);

    Serial.print("Temperature difference start to end was = ");
    Serial.print(temp_dif);
    Serial.println("*C");
    // restart if temp varies too much, otherwise we'll get inaccuracies
    if(temp_dif >= 0.05) {
        Serial.println("Temperature difference start to end must be smaller than 0.05*C, restarting");
        ecCalibrate();
    }
   return Offset;
}

// method for grabbing median of samples
double averagearray(int* arr, int number){
    int i, max, min;
    double avg;
    long amount = 0;
    
    if(number <= 0) {
        Serial.println("Error number for the array to averaging!/n");
        return 0;
    }
    if(number < 5){ // less than 5, calculated directly
        for(i=0; i<number; i++) {
            amount += arr[i];
        }
        avg = amount/number;
        return avg;
    }

    if(arr[0] < arr[1]){
        min = arr[0];
        max = arr[1];
    }
    else{
        min = arr[1];
        max = arr[0];
    }
    for(i=2; i<number; i++) {
        if(arr[i] < min) {
            amount += min;        //arr<min
            min = arr[i];
        }
        else {
            if(arr[i] > max) {
                amount += max;    //arr>max
                max = arr[i];
            }
            else{
                amount+=arr[i]; //min<=arr<=max
            }
        }
    }
    avg = (double)amount/(number-2);
    return avg;
}

// Method for converting analog output from the TDS sensor
// Sensor takes care of calculating cell constant and the base conductance 
// EC = 1000/(R*K)
// temp_regulation = 1+0.019*(temp-25)
// EC_Calibrated = EC/temp_regulation
float ECSensor::get_ec_tds() {
    float EC, voltage;
    float temp;
    int ec_index = 0;
    TempSensor temp_sensor(_temp_read);

    // Take samples of tds output
    while(ec_index<ArrayLength) {
        EC_Buf[ec_index++]=analogRead(_ec_power);
        delay(40);
    }

    voltage = averagearray(EC_Buf, ArrayLength)*5.0/1024; // get median from analog reads, convert to voltage
    temp = temp_sensor.getTemp(); // grab temp reading
    temp_reg = (1+TEMP_CO*(temp-TEMP_REG)); // calculate temp_regulation
     // multiply by 1000 to switch to microSiemens, divide by temp_reg to calibrate, add offset from calibration
    EC = (voltage*1000/temp_reg)+Offset;

    Serial.print("Voltage:");
    Serial.print(voltage, 2);
    Serial.print("    EC value: ");
    Serial.println(EC, 2);
    return EC;
}
