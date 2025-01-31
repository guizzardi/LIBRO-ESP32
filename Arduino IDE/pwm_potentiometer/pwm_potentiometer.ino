void setup() {
  Serial.begin(115200);
}

void loop() {
  // lettura analogica del pin GPIO34
  int analogValue = analogRead(34);

  // stampa del valore 0/4095:
  Serial.print("Valore Analogico: ");
  Serial.println(analogValue);
  delay(1000);
}