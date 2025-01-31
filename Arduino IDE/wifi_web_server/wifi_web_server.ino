#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "BRAIN&BYTES";
const char* password = "Inserire_la_PASSWORD";

WebServer server(80); // porta standard

void handleRoot() {
  server.send(200, "text/html", "<h1>Ciao, sono ESP32</h1>");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione al WiFi...");
  }

  Serial.println("Connesso al WiFi con successo!");

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient(); // metodo per gestire le richieste
}