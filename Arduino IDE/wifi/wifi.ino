#include <WiFi.h>

const char* ssid = "BRAIN&BYTES";
const char* password = "Inserire_la_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione al WiFi...");
  }

  Serial.println("Connesso al WiFi con successo!");
  Serial.println(WiFi.localIP());
}

void loop() {
  // ... resto del codice
}