#define Touch_Pin 4  // utilizzare i GPIO che indicano “Touch”
#define LED_BUILTIN 2

int valoreCapacitivo = 100;
int soglia = 50;  // valore di soglia regolabile

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  valoreCapacitivo = touchRead(Touch_Pin);
  Serial.print("Valore sul pin: ");
  Serial.println(valoreCapacitivo);
  if (valoreCapacitivo < soglia) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Toccato!");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(1000);
}