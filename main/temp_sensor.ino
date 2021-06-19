#include <DS18B20.h>
#include <OneWireHub.h>

//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin 2

const int TEMP_READ_PIN = A1;
const int TEMP_POWER_PIN = 8;

float getTemp() {
    float temp = 0;
    // activate temp sensor and read initial temp
    digitalWrite(TEMP_POWER_PIN, HIGH);
    temp = analogRead(TEMP_READ_PIN);
    digitalWrite(TEMP_POWER_PIN, LOW);
    
    return temp;
}

float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  // if ( OneWire::crc8( addr, 7) != addr[7]) {
  //     Serial.println("CRC is not valid!");
  //     return -1000;
  // }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return (TemperatureSum * 18 + 5)/10 + 32;
}
