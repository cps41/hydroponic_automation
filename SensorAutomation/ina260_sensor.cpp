#include <INA260Sensor.h>
#include <Adafruit_INA260.h>

Adafruit_INA260 ina260 = Adafruit_INA260();

INA260Sensor::INA260Sensor(int ina_read, int ina_power) {
    _ina_read = ina_read;
    _ina_power = ina_power;
}

float INA260Sensor::getCurrent() {
    float current;
    Serial.println("Reading Current...");
    ina260.setMode(INA260_MODE_TRIGGERED);
    current = 1000*ina260.readCurrent();
    ina260.setMode(INA260_MODE_SHUTDOWN);
    Serial.print("Current: ");
    Serial.print(current);
    Serial.print("A\n");

    return current;
}

float INA260Sensor::getVoltage() {
    float voltage;
    Serial.println("Reading Voltage...");
    ina260.setMode(INA260_MODE_TRIGGERED);
    voltage = 1000*ina260.readBusVoltage(); // convert from mV to V
    ina260.setMode(INA260_MODE_SHUTDOWN);
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.print("V\n");

    return voltage;
}

float INA260Sensor::getPower() {
    float power;
    Serial.println("Reading Power...");
    ina260.setMode(INA260_MODE_TRIGGERED);
    power = ina260.readPower();
    ina260.setMode(INA260_MODE_SHUTDOWN);
    Serial.print("Power: ");
    Serial.print(power);
    Serial.print("W\n");

    return power;
}
