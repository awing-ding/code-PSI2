#include "lib/deque.h"

#define LED 8
#define MIC A0
#define REF 735 //refrence
#define REF2 725




//A function that reads the value of the microphone and compares it to a reference value. If the value is greater than the reference value, it turns on the LED.
Deque <unsigned char> function_inutile(Deque <unsigned char> micValQueue) {
    short int micVal;
    micVal = pow(analogRead(MIC), 2);
    micValQueue.push_back(micVal >= REF or micVal <= REF2);
    unsigned char sum = 0;
    for (int i = 0; i < micValQueue.count(); i++) {
        sum += micValQueue[i];
    }
    digitalWrite(LED, sum > 14 and sum < 60);
    return micValQueue;
}

void setup() {
    long unsigned time1;
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(MIC, INPUT);
    Deque <unsigned char> micValQueue(100);
    for (int i = 0; i < 199; i++ ){
        time1 = micros();
        micValQueue = function_inutile(micValQueue);    
        int time = micros()-time1;
        Serial.println(time);
    }    
}

void loop() {}



