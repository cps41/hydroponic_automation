#include "SensorAutomation.h"
#include <OneWire.h>
#include <DallasTemperature.h>

//Temperature chip i/o
OneWire ds(TEMP_READ_PIN);
DallasTemperature sensor(&ds);

TempSensor::TempSensor(int temp_read, int temp_power) {
  _temp_read = temp_read;
  _temp_power = temp_power;
}

float TempSensor::getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius
  float temp;
  sensor.requestTemperatures();
  temp = sensor.getTempCByIndex(0);
  
  return temp;
}
