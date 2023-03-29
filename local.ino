#include "lib/deque.h"

#define LED 8
#define MIC A0
//should be change as sensibility has changed
#define REF 735 //reference -> less than 735 is the value of the microphone when there is no sound. It is used as a refe 
#define REF2 725 //reference -> more than 725 is the value of the microphone when there is no sound. It is used as a refe

#define REF3 10 // the number of time the microphone value is greater than the reference value to activate the system
#define REF4 60 // more than that should be a microphone error
#define MAX_QUEUE_SIZE 100 //the size of the queue

//A function that reads the value of the microphone and compares it to a reference value. If the value is greater than the reference value, it turns on the LED.
Deque <unsigned char> function_inutile(Deque <unsigned char> micValueQueue) {
    int micValue = analogRead(MIC);
    unsigned char count = micValueQueue.pop_back();
    unsigned char trigger = micValue > REF or micValue < REF2;
    micValueQueue.push_back(trigger);
    count += trigger;
    micValueQueue.push_back(count);
    digitalWrite(LED, count > REF3 and count < REF4);
    return micValueQueue;
}

void setup() {
    long unsigned time1;
    unsigned int time;
    Serial.begin(9600); //for debug, we should try to reduce the baud rate
    pinMode(LED, OUTPUT);
    pinMode(MIC, INPUT);
    Deque <unsigned char> micValueQueue(MAX_QUEUE_SIZE);
    for (int i = 0; i < 199; i++ ){ //some test don't worry
        time1 = micros();
        micValueQueue = function_inutile(micValueQueue);    
        time = micros()-time1;
        Serial.println(time);
    }    
}

void loop() {}
