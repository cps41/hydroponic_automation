/* 
EC Sensor Automation
Author: Carly Sills
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const int INPUT_PIN = 6;
const int A = 1; // area of electrodes
const int L = 1.5; // distance between electrodes
const int TEMP_REG = 25; // ec is regulated based on temp of 25 deg celcius

float G; // conductance
float R; // resistance
float U; // potential
float I; // current
float K = 0; // cell constant
float k; // actual conductance

const int resistor = 1000; // Value of resistor
const int READ_PIN = A0;
const int POWER_PIN = A1;
const int TEMP_PIN = A5;
const int SEC = 5;

float temp_co = 0.019;
float temp;
float EC;
float EC_temp_calib;
int ppm;
float V_readin = 0;
float V_init = 5;
float V_dif = 0;
float R_Water;
float Value = 0;

void GetEC() {
    int val;
    double Temp;
    val=analogRead(TEMP_PIN);
    // TODO: temp read in and conversion
    
    digitalWrite(POWER_PIN, HIGH); // activate sensor
    V_readin= analogRead(READ_PIN);
    digitalWrite(POWER_PIN,LOW); // deactivate sensor

    V_dif = (V_readin) / 1024.0; // convert analog readin to voltage
    R_Water = (V_dif*resistor) / (V_init-V_dif); // resistance of solution = voltage read*known resistance/voltage drop
    EC = 1/(R_Water*K); // EC = 1/(resistance*cell constant)
    EC_temp_calib = EC / (1+ temp_co*(temp-25.0)); // calculate against temp calibration

    Serial.print(" EC: ");
    Serial.print(EC_temp_calib);
    Serial.println(" microSiemens/cm \n");
    Serial.print(temp);
    Serial.print(" *C ");
}

void Calibrate () {
    Serial.println("Calibration routine started");
    float Temperature_end=0;
    float Temperature_begin=0;
    int val;
    double Temp;

    // TODO: temp read in and conversion
    Temperature_begin=Temp;
    Value = 0;
    int i=1;

    while(i<=10) {
        digitalWrite(ECPower, HIGH);
        V_readin= analogRead(EC_Read);
        digitalWrite(ECPower, LOW);
        Value=Value+V_readin;
        i++;
        delay(SEC*1000);
    };

    V_readin=(Value/10);
    val=analogRead(TEMP_PIN);

    Temperature_end=Temp;

    EC = EC_temp_calib*(1+(temp_co*(Temperature_end-25.0)));
    V_dif= (((V_init)*(V_readin))/1024.0);
    R_Water=(V_dif*resistor)/(V_init-V_dif);
    float K_cal= 1000/(R_Water*EC);

    Serial.print("Cell constant was %f, is now %f", K, K_cal);
    K = K_cal;
    Serial.print("Temperature difference start to end were = ");
    float Temp_dif = Temperature_end-Temperature_begin;
    Serial.print(Temp_dif);
    Serial.println("*C");
    Serial.println("Temperature difference start to end must be smaller than 0.15*C");
    Serial.println("");
    Calibrate ();
}