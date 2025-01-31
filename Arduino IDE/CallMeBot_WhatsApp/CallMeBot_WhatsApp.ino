#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include "time.h"

const char* ssid = "BRAIN&BYTES";
const char* password = "Inserire_la_PASSWORD";

// URL del servizio, inserire il proprio numero telefonico
String serverName = "https://api.callmebot.com/whatsapp.php?phone=391234567890&text=";

unsigned long lastTime = 0;
unsigned long timerDelay = 300000; // 5 minuti

#define DHTTYPE DHT22  // DHT22
uint8_t DHTPin = 4;
DHT dht11(DHTPin, DHTTYPE);

// variabili per i valori dei sensori
float temp;
float hum;
int potenziometro;
float voltage;
float volt;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connessione in corso");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());

  dht11.begin();
}

void loop() {
  // invio una richiesta HTTP/POST ogni 5 minuti
  if ((millis() - lastTime) > timerDelay) {
    // se la connessione al Wi-Fi è OK procedo
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      temp = dht11.readTemperature(); // lettura sensore

      String serverPath = serverName + "temperatura:" + temp + "&apikey=5336178";

      // avvio comunicazione all'URL
      http.begin(serverPath.c_str());

      // invio richiesta HTTP/GET e memorizzo la risposta
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      } else {
        Serial.print("Codice errore: ");
        Serial.println(httpResponseCode);
      }
      // chiudo la comunicazione
      http.end();
    } else {
      Serial.println("WiFi Scollegato");
    }
    lastTime = millis();
  }
}