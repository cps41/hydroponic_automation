#include "SensorAutomation.h"
#include <stdio.h>
#include <LiquidCrystal.h>

const unsigned long int REG_EC_INTERVAL = 60*60*1000; // Regular interval for EC loop is 1 hour
const double REG_PH_INTERVAL = 10*1000; // Regular pH loop will occur 10 minutes after EC loop

int ec_analog = A0;
int ph_read = A2;
int temp_read = 1;

LiquidCrystal lcd(2,3,4,5,6,7);

// Mux pins to control Pumps
int up_pump = 8;
int down_pump = 9;
int nutrient_pump = 10;

SensorAutomation automate(ec_analog, ph_read, temp_read,
                        up_pump, down_pump, nutrient_pump);

void setup() {
    // set up serial and lcd screen
    Serial.begin(9600);
    Serial.println("Ready");
    lcd.begin(32,2);
    lcd.print("Welcome to ForwardGardyn!");
    lcd.setCursor(0, 1);
    lcd.print("Calibration routine beginning...");

	// set pump pin outputs
	// run calibration routine to calculate EC offset
    pinMode(up_pump, OUTPUT);
    pinMode(down_pump, OUTPUT);
    pinMode(nutrient_pump, OUTPUT);
    automate.calibrateEC();
    
    Serial.println("Calibration Done");
    lcd.setCursor(0, 1);
    lcd.print("Calibration Done");

	// give user time to place sensor back in basin
    for (int i = 30; i > 0 ; i--) {
      lcd.setCursor(0, 1);
      lcd.print(String(i) + " Seconds Left To Put Sensors In Basin");
      Serial.println(String(i) + " Seconds Left To Put Sensors In Basin");
      delay(1000);
    }

    lcd.setCursor(0, 1);
    lcd.print("Calibration Done");
    Serial.println("Beginning Regulation");
    delay(1000);
}

void loop() {
	// clear screen
    lcd.clear();
	
    automate.checkEC();
    delay(1000);
    automate.checkPH(); // enter pH loop to maintain levels
    delay(1000);
}
