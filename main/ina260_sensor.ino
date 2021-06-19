#include <Adafruit_INA260.h>

Adafruit_INA260 ina260 = Adafruit_INA260();

float readCurrent(void) {
    float current;
    ina260.setMode(INA260_MODE_TRIGGERED);
    current = ina260.readCurrent();
    ina260.setMode(INA260_MODE_SHUTDOWN);

    return current;
}

float readVoltage(void) {
    float voltage;
    ina260.setMode(INA260_MODE_TRIGGERED);
    voltage = ina260.readBusVoltage();
    ina260.setMode(INA260_MODE_SHUTDOWN);

    return voltage;
}

float readPower(void) {
    float power;
    ina260.setMode(INA260_MODE_TRIGGERED);
    power = ina260.readPower();
    ina260.setMode(INA260_MODE_SHUTDOWN);

    return power;
}
