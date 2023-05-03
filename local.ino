//lib with the deque class
#include "lib/deque.h" 

//import function prototype
#include "local.h"

//the pins
#define LED 8
#define MIC A0 

//references to detect a trigger
#define REF 39
#define REF2 41

//the number of time the microphone value is greater or inferior than the reference value to activate the system
#define REF3 20 // the number of time the microphone value is greater than the reference value to activate the system
#define REF4 60 // more than that should be a microphone error or dumb ppl that hit the mic

//the size of the queue
#define MAX_QUEUE_SIZE 100 


void setup() {
    //sets the pins
    pinMode(LED, OUTPUT);
    pinMode(MIC, INPUT);

    //creates the queue, fill it and get a pointer to it
    Deque <unsigned char> queue_of_time_it_was_triggered(MAX_QUEUE_SIZE);
    fill_queue(&queue_of_time_it_was_triggered);
    Deque <unsigned char> * pointer_of_triggers_queue = &queue_of_time_it_was_triggered;

    //starts the main function, not the arduino loop but a home-made one
    pseudo_main(pointer_of_triggers_queue);
}

//the main function
void pseudo_main(Deque <unsigned char> * const pointer_of_triggers_queue){
    //a forever loop that checks if there is an alarm
    while (1){
        is_there_alarm(pointer_of_triggers_queue);
    }
}

//A function that reads the value of the microphone and compares it to a reference value. If the value is greater than the reference value, it turns on the LED.
void is_there_alarm(Deque <unsigned char> * const queue_of_time_it_was_triggered) {
    unsigned char number_of_time_triggered = queue_of_time_it_was_triggered->pop_back();
    number_of_time_triggered -= queue_of_time_it_was_triggered->pop_front();

    //reads the value of the microphone and compares it to a reference value
    int value_of_mic = analogRead(MIC);
    unsigned char trigger = (value_of_mic > REF or value_of_mic < REF2); //1 if there is a trigger, 0 if not
    queue_of_time_it_was_triggered->push_back(trigger);
    //use a counter value to be faster
    number_of_time_triggered += trigger;
    queue_of_time_it_was_triggered->push_back(number_of_time_triggered);

    //if the number of time the microphone value is greater than the reference value is greater than REF3, it turns on the LED
    //as more than REF4 is considered as a microphone error, it turns off the LED
    digitalWrite(LED, number_of_time_triggered > REF3 and number_of_time_triggered < REF4);
}

void fill_queue(Deque <unsigned char> * const queue_of_time_it_was_triggered){
    for (int i = 0; i < MAX_QUEUE_SIZE; i++){
        queue_of_time_it_was_triggered->push_back(0);
    }
}

//as we didn't really know how it works, we made our own loop
//but as it's mandatory to have it, we made it empty
void loop() {}
