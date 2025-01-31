#define LIGHT_SENSOR_PIN 34 // ESP34 pin GIOP34 (ADC1_6)

void setup() {
  Serial.begin(115200);

  // imposto l'attenuazione a 11 dB (~3.3V input)
  analogSetAttenuation(ADC_11db);
}

void loop() {
  // lettura del valore analogico (compreso tra 0 e 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Luminosità: ");
  Serial.print(analogValue); 

  // indico la luminosità in base al valore
  if (analogValue < 40) {
    Serial.println(" => Luce diretta");
  } else if (analogValue < 800) {
    Serial.println(" => Luminoso");
  } else if (analogValue < 2000) {
    Serial.println(" => Luce");
  } else if (analogValue < 3200) {
    Serial.println(" => Penombra");
  } else {
    Serial.println(" => Buio");
  }

  delay(500);
}