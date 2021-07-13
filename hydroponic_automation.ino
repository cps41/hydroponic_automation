#include "SensorAutomation.h"
#include <stdio.h>

const unsigned long int REG_EC_INTERVAL = 60*60*1000; // Regular interval for EC loop is 1 hour
const double REG_PH_INTERVAL = 10*1000; // Regular pH loop will occur 10 minutes after EC loop

int ec_analog = A0;
int ph_read = A2;
int temp_read = 2;
int up_pump = 8;
int down_pump = 9;
int nutrient_pump = 10;

SensorAutomation automate(ec_analog, ph_read, temp_read,
                        up_pump, down_pump, nutrient_pump);

void setup() {
    Serial.begin(9600);
    Serial.println("Ready");
    pinMode(up_pump, OUTPUT);
    pinMode(down_pump, OUTPUT);
    pinMode(nutrient_pump, OUTPUT);
    automate.calibrateEC();
    delay(1500);
}

void loop() {
    automate.checkEC();
    delay(1000);
    automate.checkPH(); // enter pH loop to maintain levels
    delay(1000);
}


