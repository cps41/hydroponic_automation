#include "INA260Sensor.h"
#include <Adafruit_INA260.h>


INA260Sensor::INA260Sensor(uint8_t addr=INA260_I2CADDR_DEFAULT) {
    ina260 = Adafruit_INA260();
    if (!ina260.begin(addr)) {
        Serial.println("Couldn't find INA260 chip");
        while (1);
    }
    Serial.println("Found INA260 chip");
}

float INA260Sensor::getCurrent() {
    float current;
    Serial.print("Reading Current...\n");
    ina260.setMode(INA260_MODE_TRIGGERED);
    current = ina260.readCurrent();
    ina260.setMode(INA260_MODE_SHUTDOWN);

    return current;
}

float INA260Sensor::getVoltage() {
    float voltage;
    Serial.print("Reading Voltage...\n");
    ina260.setMode(INA260_MODE_TRIGGERED);
    voltage = 1000*ina260.readBusVoltage(); // convert from mV to V
    ina260.setMode(INA260_MODE_SHUTDOWN);

    return voltage;
}

float INA260Sensor::getPower() {
    float power;
    ina260.setMode(INA260_MODE_TRIGGERED);
    power = ina260.readPower();
    ina260.setMode(INA260_MODE_SHUTDOWN);

    return power;
}
