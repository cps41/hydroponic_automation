#include "INA260Sensor.h"

INA260Sensor ina_current;
INA260Sensor ina_voltage;

void setup() {
  Serial.begin(9600);
  // Wait until serial port is opened
  while (!Serial) { delay(10); }
  Serial.println("INA260 Test...");
  ina_current = INA260Sensor(0x40);
  ina_voltage = INA260Sensor(0x44);
}

void loop() {
  Serial.print("Current: ");
  Serial.print(ina_current.getCurrent());
  Serial.println("A");

  Serial.print("Bus Voltage: ");
  Serial.print(ina_voltage.getVoltage());
  Serial.println("V");

  Serial.println();
  delay(1000);
}