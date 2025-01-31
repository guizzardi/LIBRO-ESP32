const int trigPin = 5;
const int echoPin = 18;

// impostiamo la velocità del suono
#define SOUND_SPEED 0.034

long durata;
float distanza;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW); // porto basso il trig 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // porto alto il trig per 10 us
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // poi lo riporto basso

  durata = pulseIn(echoPin, HIGH); // leggo il ritorno dell'impulso

  distanza = durata * SOUND_SPEED / 2; // calcolo la distanza

  // Prints the distance in the Serial Monitor
  Serial.print("Distanza: ");
  Serial.print(distanza);
  Serial.println(" Cm.");

  delay(2000);
}