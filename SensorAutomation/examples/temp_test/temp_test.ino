#include "TempSensor.h"

TempSensor temp_sense(2, 6);
void setup() {
    Serial.begin(9600);
    Serial.println("Ready");
}

void loop() {
    temp_sense.getTemp();
    delay(1000);
}