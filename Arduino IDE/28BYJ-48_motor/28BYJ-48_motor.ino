#include <AccelStepper.h>

// definizione dei pin del motore
#define IN1 16
#define IN2 17
#define IN3 18
#define IN4 19

// configurazione del motore passo-passo con AccelStepper
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

void setup() {
  // imposta la velocità massima e l'accelerazione
  stepper.setMaxSpeed(1000); // passi per secondo
  stepper.setAcceleration(500); // passi per secondo quadrato

  // imposta la posizione iniziale
  stepper.setCurrentPosition(0);
}

void loop() {
  // comando per far ruotare il motore avanti e indietro
  if (stepper.currentPosition() == 0) {
    stepper.moveTo(2048); // 2048 passi = 1 giro completo (28BYJ-48)
  }
  if (stepper.currentPosition() == 2048) {
    stepper.moveTo(0);
  }

  // fa avanzare il motore
  stepper.run();
}
