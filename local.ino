#include <arduinoFFT.h>

#define SAMPLES 512             // nombre d'échantillons
#define SAMPLING_FREQUENCY 44100 // fréquence d'échantillonnage en Hz

int ledPin = 13;              // broche de la LED
int micPin = A0;              // broche du microphone

arduinoFFT FFT = arduinoFFT();  // Créer un objet FFT

double vReal[SAMPLES];
double vImag[SAMPLES];
double freqValues[100] = {0};
int freqIndex = 0;
int freqCount = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  ADCSRA |=  bit (ADPS2) | bit (ADPS1); // définir la fréquence d'échantillonnage à 44,1 kHz
}

void loop() {
  // Lecture des échantillons analogiques
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(micPin);  // Lecture de l'entrée analogique du microphone
    vImag[i] = 0;
  }

  // Appliquer une fenêtre de Hamming aux données
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = vReal[i] * (0.54 - 0.46 * cos(2 * PI * i / (SAMPLES - 1)));
  }
  
  // Exécution de la transformée de Fourier
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  
  // Ajouter la fréquence à la liste des fréquences précédentes
  freqValues[freqIndex] = peak;
  freqIndex = (freqIndex + 1) % 100;
  
  // Calculer le nombre de fréquences comprises entre 8000 et 9000 Hz dans les 100 dernières valeurs
  freqCount = 0;
  for (int i = 0; i < 50; i++) {
    if (freqValues[i] >= 8000 && freqValues[i] <= 11000) {
      freqCount++;
    }
  }

  // Vérification si le nombre de fréquences entre est suffisant pour étre une alarme incendie
  if (freqCount >= 50/5) {
    // Allumer la LED si la fréquence est détectée
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Affichage de la fréquence
  Serial.print("Frequency: ");
  Serial.print(peak);
  Serial.print(" Hz, Frequencies between 8000 and 11000 Hz: ");
  Serial.print(freqCount);
  Serial.println();

  delay(100);
}
