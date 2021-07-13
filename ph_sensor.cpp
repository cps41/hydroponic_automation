#include "PHSensor.h"

static float OffsetPH = 0.00 ;
const int ArrayLength = 40; // samples
int PH_Buf[ArrayLength]; // Store the average value of the sensor feedback

PHSensor::PHSensor(int ph_read) {
  _ph_read = ph_read;
}

// method for grabbing median of samples
double ph_averagearray(int* arr, int number){
    int i;
    int max,min;
    double avg;
    long amount=0;
    
    if(number <= 0) {
        Serial.println("Error number for the array to averaging!/n");
        return 0;
    }

    if(number < 5){ // less than 5, calculated directly
        for(i=0; i<number; i++) {
            amount += arr[i];
        }
        avg = amount/number;
        return avg;
    }

    if(arr[0] < arr[1]){
        min = arr[0];
        max = arr[1];
    }
    else{
        min = arr[1];
        max = arr[0];
    }
    for(i=2; i<number; i++) {
        if(arr[i] < min) {
            amount += min;        //arr<min
            min = arr[i];
        }
        else {
            if(arr[i] > max) {
                amount += max;    //arr>max
                max = arr[i];
            }
            else{
                amount+=arr[i]; //min<=arr<=max
            }
        }
    }
    avg = (double)amount/(number-2);
    return avg;
}

float PHSensor::getPH() {
    int ph_index=0;
    float PH, voltage;

    // Take samples of pH output
    while(ph_index<ArrayLength) {
        int cur = analogRead(_ph_read);
        Serial.println(cur);
        PH_Buf[ph_index++] = cur;
        delay(40);
    }

    ph_index = 0;
    voltage = ph_averagearray(PH_Buf, ArrayLength)*5.0/1024/6; // convert median of samples to mV
    PH = (3.5 * voltage) + OffsetPH; // convert to pH
    Serial.print("Voltage:");
    Serial.print(voltage,3);
    Serial.print("mV    pH value: ");
    Serial.println(PH,3);
    return PH;
}
