#include "SensorAutomation.h"
#include <Adafruit_INA260.h>

Adafruit_INA260 ina260 = Adafruit_INA260();

INA260Sensor::INA260Sensor(int ina_read, int ina_power) {
    _ina_read = ina_read;
    _ina_power = ina_power;
}

float INA260Sensor::getCurrent() {
    float current;
    ina260.setMode(INA260_MODE_TRIGGERED);
    current = ina260.readCurrent();
    ina260.setMode(INA260_MODE_SHUTDOWN);

    return current;
}

float INA260Sensor::getVoltage() {
    float voltage;
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
