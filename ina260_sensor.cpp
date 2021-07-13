#include "INA260Sensor.h"
#include <Adafruit_INA260.h>


INA260Sensor::INA260Sensor(uint8_t addr=INA260_I2CADDR_DEFAULT) {
    ina260 = Adafruit_INA260();
    // if (!ina260.begin(addr)) {
    //     Serial.print("Couldn't find INA260 chip with address: ");
    //     Serial.println(addr);
    //     while (1);
    // }
//    Serial.print("Found INA260 chip with address ");
//    Serial.println(addr);
}

float INA260Sensor::getCurrent() {
    float current;
//    Serial.print("Reading Current...\n");
    // ina260.setMode(INA260_MODE_TRIGGERED);
    current = -ina260.readCurrent();
    // ina260.setMode(INA260_MODE_SHUTDOWN);
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println("mA");

    return current;
}

float INA260Sensor::getVoltage() {
    float voltage;
//    Serial.print("Reading Voltage...\n");
    // ina260.setMode(INA260_MODE_TRIGGERED);
    voltage = ina260.readBusVoltage(); // convert from mV to V
    // ina260.setMode(INA260_MODE_SHUTDOWN);
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("mV");

    return voltage;
}

float INA260Sensor::getPower() {
    float power;
    ina260.setMode(INA260_MODE_TRIGGERED);
    power = ina260.readPower()/1000.0;
    ina260.setMode(INA260_MODE_SHUTDOWN);
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println("mW");

    return power;
}
