#include "TempSensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

TempSensor::TempSensor(int temp_read) {
  _temp_read = temp_read;
}

float TempSensor::getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius
  //Temperature chip i/o
  OneWire ds(_temp_read);
  DallasTemperature sensor(&ds);
  float temp;
  sensor.requestTemperatures();
  temp = sensor.getTempCByIndex(0);
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println("*C");
  
  return temp;
}
