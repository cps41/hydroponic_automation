#include <ECSensor.h>

int ec_read = A0;
int ec_power = 4;
int ph_read = A1;
int ph_power = 5;
int temp_read = 2;
int temp_power = 6; 
int ina_read = A3;
int ina_power = 7;
int up_pump = 8;
int down_pump = 9;
int nutrient_pump = 10;

ECSensor ec_sense(ec_read, ec_power,
                          temp_read, temp_power, 
                          ina_read, ina_power);

void setup() {
    Serial.begin(57600);
    Serial.println("Ready");
    //ec_sense.calibrateEC(); // calibrate EC sensor
}

void loop() {
    Serial.println("Looping");
    ec_sense.getEC(); // enter EC loop to maintain levels
    delay(1000); // delay before pH check
}
