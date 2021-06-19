/* 
EC Sensor Automation
Author: Carly Sills
*/
#include <temp_sensor.ino>
#include <ina260_sensor.ino>

const int INPUT_PIN = 6;
const float A = 10; // area of electrodes
const float L = 1; // distance between electrodes
const float TEMP_REG = 25.0; // ec is regulated based on temp of 25 deg celcius

float G; // conductance
float R; // resistance
float U; // potential
float I; // current
float K = L/A; // cell constant
float k; // actual conductance

const float EC_CALIB; // TBD

const int resistor = 1000; // Value of resistor
const int EC_READ_PIN = A0;
const int EC_POWER_PIN = 7;
const int READ_DELAY = 5000;

/*
    Function to read value from EC sensor and convert it to usable data

    return: EC: (float) conductivity detected by sensor
*/
float getEC() {
    float avg_ec_voltage;
    float temp_co = 0.019;
    float temp;
    float EC;
    float EC_uncalibrated;
    float V_init = 5;
    float V_in = 0;
    float R_Water = 0;

    digitalWrite(EC_POWER_PIN, HIGH); // activate sensor
    V_in = analogRead(EC_READ_PIN); // read voltage
    digitalWrite(EC_POWER_PIN,LOW); // deactivate sensor
    temp = getTemp(); // get temperature

    V_in = V_in*V_init/1024.0; // convert analog readin to voltage
    R = V_in*resistor/(V_init-V_in); // resistance of solution = voltage read*known resistance/voltage drop
    EC_uncalibrated = 1000/(R*K); // EC = 1000/(resistance*cell constant)
    EC = EC_uncalibrated*1000 / (1+temp_co*(temp-25.0)); // calculate against temp calibration

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
void ecCalibrate () {
    float temp_start, temp_end;
    float avg_ec_voltage;
    float temp_co = 0.019;
    float temp;
    float EC;
    float EC_uncalibrated;
    float V_init = readVoltage();
    float V_in;
    float R_Water;
    float temp_dif;
    float K_cal;

    Serial.println("Calibration routine started");
    digitalWrite(EC_POWER_PIN, HIGH); // power sensor
    temp_start = getTemp();

    // get average ec output across sample size of n
    for(int i=0; i<10; i++) {
        // activate ec sensor and read
        avg_ec_voltage += analogRead(EC_READ_PIN);
        delay(READ_DELAY);
    }

    digitalWrite(EC_POWER_PIN, LOW); // shutdown sensor
    temp_end = getTemp();
    V_in = avg_ec_voltage/10;
    temp_dif = temp_start-temp_end;
    temp = (temp_start+temp_end)/2;

    V_in = V_in*V_init/1024.0; // convert analog readin to voltage
    R = V_in*resistor/(V_init-V_in); // resistance of solution = voltage read*known resistance/voltage drop
    EC = EC_CALIB / (1+temp_co*(temp_end-25.0)); // Calibrated EC = EC_25/(1 + α(t-25))
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
