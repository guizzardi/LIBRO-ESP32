#include <Arduino.h>

// definizione dei pin
#define RELAY1_PIN 23
#define RELAY2_PIN 22

// stato dei relè
bool relay1State = false;
bool relay2State = false;

void setup() {
  // configurazione pin relè come output
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  // inizializza relè in stato spento
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);

  Serial.begin(115200);
  Serial.println("Test a due relè avviato.");
}

void loop() {
  relay1State = !relay1State;  // inverti lo stato del relè
  digitalWrite(RELAY1_PIN, relay1State ? HIGH : LOW);
  Serial.print("Relè 1 stato: ");
  Serial.println(relay1State ? "ON" : "OFF");

  relay2State = !relay2State;  // inverti lo stato del relè
  digitalWrite(RELAY2_PIN, relay2State ? HIGH : LOW);
  Serial.print("Relè 2 stato: ");
  Serial.println(relay2State ? "ON" : "OFF");
  delay(5000);
}
