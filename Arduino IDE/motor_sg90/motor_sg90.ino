#include <ESP32Servo.h>  // libreria per il servo SG90

static const int servoPin = 32; // GPIO PWM utilizzato per il segnale

Servo servo1; // istanzia di un oggetto della classe Servo

void setup() {
  Serial.begin(115200);  
  servo1.attach(servoPin);
}

void loop() {
  // effettua una rotazione da 0 a 180 gradi
  for (int posDegrees = 0; posDegrees <= 180; posDegrees++) {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }

  // effettua una rotazione da 180 a 0 gradi
  for (int posDegrees = 180; posDegrees >= 0; posDegrees--) {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}