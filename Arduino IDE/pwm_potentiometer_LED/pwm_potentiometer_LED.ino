#define potenziometro 34  // GPIO34 (ADC1_6) per il potenziometro
#define LED 27            // GPIO27 per il LED

void setup() {
  Serial.begin(115200);

  analogSetAttenuation(ADC_11db);  // imposta gamma da 0 a 3,3V

  pinMode(LED, OUTPUT);
}

void loop() {
  int valore = analogRead(potenziometro);  // lettura del potenziometro

  // proporzione tra i due range
  int luminosita = map(valore, 0, 4095, 0, 1023);

  analogWrite(LED, luminosita);  // imposta la luminosità

  Serial.print("Valore: ");
  Serial.print(valore);
  Serial.print(" => Luminosità = ");
  Serial.println(luminosita);
  
  delay(300);
}