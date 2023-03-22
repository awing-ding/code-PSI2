#include "lib/deque.h"

#define LED 8
#define MIC A0
#define REF 735 //refrence
#define REF2 725


short int micVal ;
void function_inutile();

Deque <unsigned char> micValQ ;

long unsigned time1;

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(MIC, INPUT);
    for (int i = 0; i < 199; i++ ){
    function_inutile();    
    }
    time1 = micros();
    function_inutile2();
    int time = micros()-time1;
    Serial.println(time);
    
}

void loop() {}

void function_inutile2() {
    micVal = pow(analogRead(MIC), 2);
    //Serial.print("mic:");
    //Serial.println(micVal);
    micValQ.push_back(micVal >= REF or micVal <= REF2);
    if (micValQ.count() > 100) {
        micValQ.pop_front();
    }
    unsigned char sum = 0;
    for (int i = 0; i < micValQ.count(); i++) {
        sum += micValQ[i];
    }
    digitalWrite(LED, sum > 14 and sum < 60);

    //Serial.print("sum: ");
    //Serial.println(sum);

    //delay(1);
}

void function_inutile() {
    micVal = pow(analogRead(MIC), 2);
    //Serial.print("mic:");
    //Serial.println(micVal);
    micValQ.push_back(micVal >= REF or micVal <= REF2);
    if (micValQ.count() > 100) {
        micValQ.pop_front();
    }
    unsigned char sum = 0;
    for (int i = 0; i < micValQ.count(); i++) {
        sum += micValQ[i];
    }
    digitalWrite(LED, sum > 14 and sum < 60);

    //Serial.print("sum: ");
    //Serial.println(sum);

    //delay(1);
}
