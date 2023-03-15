#include "lib/deque.h"

#define LED 8
#define MIC A0
#define REF 950 //refrence


short int micVal ;

Deque <int> micValQ ;



void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(MIC, INPUT);
    
}

void loop() {
    micVal = pow(analogRead(MIC), 2);
    if (micVal >= REF) {
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

    if (sum > 11) {
        digitalWrite(LED, HIGH);
    }
    else {
        digitalWrite(LED, LOW);
    }

    Serial.print("sum: ");
    Serial.println(sum);

    delay(2);

    
}
