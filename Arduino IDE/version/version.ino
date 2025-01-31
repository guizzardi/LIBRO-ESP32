void setup() {
  Serial.begin(115200);
  delay(2000);

  auto ver = __cplusplus;
  Serial.print("C++ Version: ");
  Serial.println(ver);
}

void loop() {
}