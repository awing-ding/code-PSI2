#include "lib/deque.h"

#define LED 8
#define MIC A0
//sensibility has changed so ref should be changed too
#define REF 735 //reference -> less than 735 is the value of the microphone when there is no sound. It is used as a refe
#define REF2 725 //reference -> more than 725 is the value of the microphone when there is no sound. It is used as a refe

#define REF3 10 // the number of time the microphone value is greater than the reference value to activate the system
#define REF4 60 // more than that should be a microphone error
#define MAX_QUEUE_SIZE 100 //the size of the queue

//A function that reads the value of the microphone and compares it to a reference value. If the value is greater than the reference value, it turns on the LED.
void function_inutile(Deque <unsigned char> * const micValQueue) {
    int micVal;
    unsigned char count = micValQueue->pop_back();
    int micVal = analogRead(MIC);
    unsigned char trigger = micVal > REF or micVal < REF2;
    micValQueue->push_back(trigger);
    count += trigger;
    micValQueue->push_back(count);
    digitalWrite(LED, count > REF3 and count < REF4);
}

void setup() {
    long unsigned time1;
    unsigned int time;
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(MIC, INPUT);
    Deque <unsigned char> micValQueue(MAX_QUEUE_SIZE);
    for (int i = 0; i < MAX_QUEUE_SIZE; i++){
        micValQueue.push_back(0);
    }
    Deque <unsigned char> * micValQueuePtr = &micValQueue;
    /*for (int i = 0; i < 199; i++ ){ //some test don't worry
        time1 = micros();
        function_inutile(micValQueuePtr);    
        time = micros()-time1;
        Serial.println(time);
    }*/
    main(micValQueuePtr);
}

void main(Deque <unsigned char> * const micValQueuePtr){
    while (1){
        //function_inutile(micValQueuePtr);
        Serial.println(analogRead(MIC));
    }
}
void loop() {}
