#define LED 8
#define MIC A0
#define REF 735 //reference -> less than 735 is the value of the microphone when there is no sound. It is used as a refe
#define REF2 725 //reference -> more than 725 is the value of the microphone when there is no sound. It is used as a refe

#define REF3 10 // the number of time the microphone value is greater than the reference value to activate the system
#define REF4 60 // more than that should be a microphone error
#define MAX_QUEUE_SIZE 100 //the size of the queue

//A function that reads the value of the microphone and compares it to a reference value. If the value is greater than the reference value, it turns on the LED.
char function_inutile(char count) {
    short int micVal;
    micVal = pow(analogRead(MIC), 2);
    if (micVal >= REF or micVal <= REF2){
        count ++;
        if (count > 100){
            count  -= 2;
        }
    }
    else {
        count --;
    }
    digitalWrite(LED, count > REF3 and count < REF4);
    return count;
}

void setup() {
    long unsigned time1;
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(MIC, INPUT);
    char count = 0;
    for (int i = 0; i < 199; i++ ){ //some test don't worry
        time1 = micros();
        count = function_inutile(count);    
        int time = micros()-time1;
        Serial.println(time);
    }    
}

void loop() {}
