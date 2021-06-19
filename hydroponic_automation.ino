#include <LiquidCrystal.h>
#include "ec_sensor.ino"

const double REG_EC_INTERVAL = 60*60*1000; // Regular interval for EC loop is 1 hour
const double REG_PH_INTERVAL = 60*10*1000; // Regular pH loop will occur 10 minutes after EC loop
const int EC_THRESH_INTERVAL = 3*1000; // Interval for reading EC when adjusting to re-enter threshold
const int PH_THRESH_INTERVAL = 3*1000; // Interval for reading pH when adjusting to re-enter threshold

void setup() {
    Serial.begin(9600);
    Serial.println("Ready");
}

void loop() {
    ecCalibrate();
}
