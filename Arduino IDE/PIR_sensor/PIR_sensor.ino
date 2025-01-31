const int PIR = 23;

void setup() {
  pinMode(PIR, INPUT);
  Serial.begin(115200);
}

void loop() {
  int sensore = digitalRead(PIR);

  if( sensore == LOW ) {
   Serial.println("Presenza non rilevata.");
  }
  else {
    Serial.println("Presenza rilevata!");  
  }
  delay(1000);
}