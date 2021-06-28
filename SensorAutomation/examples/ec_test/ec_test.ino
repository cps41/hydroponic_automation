#include "ECSensor.h"

ECSensor ec_sense(1, 2, 3);

void setup() {
    Serial.begin(9600);
    Serial.println("Ready");
    //ec_sense.calibrateEC(); // calibrate EC sensor
}

void loop() {
    Serial.println("Looping");
    ec_sense.getEC(); // enter EC loop to maintain levels
    delay(1000); // delay before pH check
}
