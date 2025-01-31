#include <WiFi.h>

const char* ssid = "ESP32_ACCESS_POINT";
const char* password = "Inserire_la_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
 
  Serial.println("Access point creato!");
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // ...resto del codice
}