#include "SensorAutomation.h"

unsigned long int average;

const int PH_POWER_PIN = 9;
const int PH_READ_PIN = A2;
const int PH_READ_DELAY = 1000;
const float OFFSET = 0.0; // TBD

PHSensor::PHSensor(int ph_read, int ph_power) {
  _ph_read = ph_read;
  _ph_power = ph_power;
}

float PHSensor::getPH() {
  float avg_ph_voltage;
  float ph;

  digitalWrite(PH_POWER_PIN, HIGH); // power sensor
  delay(PH_READ_DELAY); // let settle
  
  for(int i=0; i<10; i++) {
    avg_ph_voltage += analogRead(PH_READ_PIN);
    delay(PH_READ_DELAY);
  }
  digitalWrite(PH_POWER_PIN, LOW); // deactivate sensor

  avg_ph_voltage /= 10;
  ph = avg_ph_voltage * 5 / 1024 / 6; // convert to mV
  ph = 3.5 * ph + OFFSET; // convert to pH

  Serial.print("pH: ");
  Serial.println(ph);

  return ph;
}
