#include "lib/deque.h"

#define LED 8
#define MIC A0
#define REF 735 //refrence
#define REF2 725


short int micVal ;

Deque <int> micValQ ;



void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(MIC, INPUT);
    
}

void loop() {
    micVal = pow(analogRead(MIC), 2);
    Serial.print("mic:");
    Serial.println(micVal);
    if (micVal >= REF or micVal <= REF2) {
        micValQ.push_back(1);
    }
    else {
        micValQ.push_back(0);
    }
    if (micValQ.count() > 100) {
        micValQ.pop_front();
    }
    int sum = 0;
    for (int i = 0; i < micValQ.count(); i++) {
        sum += micValQ[i];
    }

    if (sum > 14 and sum < 60) {
        digitalWrite(LED, HIGH);
    }
    else {
        digitalWrite(LED, LOW);
    }

    //Serial.print("sum: ");
    //Serial.println(sum);

    delay(1);

    
}
