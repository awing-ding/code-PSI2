#include "lib/deque.h"

#define LED 8
#define MIC A0
#define REF 735 //reference -> less than 735 is the value of the microphone when there is no sound. It is used as a refe
#define REF2 725 //reference -> more than 725 is the value of the microphone when there is no sound. It is used as a refe

#define REF3 10 // the number of time the microphone value is greater than the reference value to activate the system
#define REF4 60 // more than that should be a microphone error
#define MAX_QUEUE_SIZE 75 //the size of the queue

//A function that reads the value of the microphone and compares it to a reference value. If the value is greater than the reference value, it turns on the LED.
Deque <unsigned char> function_inutile(Deque <unsigned char> micValQueue) {
    short int micVal;
    micVal = pow(analogRead(MIC), 2);
    micValQueue.push_back(micVal >= REF or micVal <= REF2);
    unsigned char sum = 0;
    for (int i = 0; i < micValQueue.count(); i++) {
        sum += micValQueue[i];
    }
    digitalWrite(LED, sum > REF3 and sum < REF4);
    return micValQueue;
}

void setup() {
    long unsigned time1;
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(MIC, INPUT);
    Deque <unsigned char> micValQueue(MAX_QUEUE_SIZE);
    for (int i = 0; i < 199; i++ ){ //some test don't worry
        time1 = micros();
        micValQueue = function_inutile(micValQueue);    
        int time = micros()-time1;
        Serial.println(time);
    }    
}

void loop() {}
