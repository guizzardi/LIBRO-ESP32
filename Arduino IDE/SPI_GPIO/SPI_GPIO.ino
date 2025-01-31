void setup() {
  Serial.begin(115200);

  // richiedo e visualizzo le porte SPI
  Serial.print("MOSI Pin: ");
  Serial.println(MOSI);
  Serial.print("MISO Pin: ");
  Serial.println(MISO);
  Serial.print("SCK Pin: ");
  Serial.println(SCK);
  Serial.print("SS Pin: ");
  Serial.println(SS);  
}

void loop() {}