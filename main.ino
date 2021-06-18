// Software by Pierre Hertzog YouTube channel (AgriTech with Pierre) (2020)
// You are welcome to use my software as long as recognition is given to my YouTube channel
// Connections (Also see Video)
// One pin of EC probe to Arduino Gnd
// One pin of EC probe to 1k resistor and to pin A1 of Arduino
// Other pin of resistor to A0
// One pin of thermistor to A5 and one side of 10k resistor
// Other pin of thermistor to 5V on Arduino
// Other pin of 10k resistor to Gnd

void setup() {
    Serial.begin(9600);
    pinMode(EC_Read, INPUT);
    pinMode(ECPower, OUTPUT);
    //////////////////////////////////////////////////////////////////////////////////////////
    Calibrate (); // After calibration put two forward slashes before this line of code
    //////////////////////////////////////////////////////////////////////////////////////////
}

void loop() {
    GetEC(); //Calls GetEC()
    delay(6000); //Do not make this less than 6 sec (6000)
}