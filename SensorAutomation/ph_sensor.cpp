#include "PHSensor.h"

const int PH_READ_DELAY = 1000;
const float OFFSET = 0.0; // TBD

PHSensor::PHSensor(int ph_read, int ph_power) {
  _ph_read = ph_read;
  _ph_power = ph_power;
}

float PHSensor::getPH() {
  float avg_ph_voltage;
  float ph;

  digitalWrite(_ph_power, HIGH); // power sensor
  delay(PH_READ_DELAY); // let settle
  
  for(int i=0; i<10; i++) {
    avg_ph_voltage += analogRead(_ph_read);
    delay(PH_READ_DELAY);
  }
  digitalWrite(_ph_power, LOW); // deactivate sensor

  avg_ph_voltage /= 10;
  ph = avg_ph_voltage * 5 / 1024 / 6; // convert to mV
  ph = 3.5 * ph + OFFSET; // convert to pH

  Serial.print("pH: ");
  Serial.println(ph);

  return ph;
}
