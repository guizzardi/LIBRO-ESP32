#define SENSOR_PIN 34 // GPIO36 (ADC1_6)

int lastState = HIGH;  // ultimo stato del pin
int currentState;      // stato corrente del pin

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT); // inizializzo il pin
}

void loop() {
  // leggo lo stato del pin
  currentState = digitalRead(SENSOR_PIN);

  if (lastState == HIGH && currentState == LOW)
    Serial.println("Rilevato suono!");
  else if (lastState == LOW && currentState == HIGH)
    Serial.println("Rilevamento cessato.");

  lastState = currentState; // salvo l'ultimo stato
}