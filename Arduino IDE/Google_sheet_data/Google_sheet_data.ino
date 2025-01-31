#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include "DHT.h"
#include "time.h"
#include <Adafruit_Sensor.h>
#include <ESP_Google_Sheet_Client.h>

#define WIFI_SSID "BRAIN&BYTES"
#define WIFI_PASSWORD "Inserire_la_PASSWORD"

// ID del progetto su Google
#define PROJECT_ID "uplifted-road-447810-i4"

// account email di servizio
#define CLIENT_EMAIL "esp32-test-142@uplifted-road-447810-i4.iam.gserviceaccount.com"

// chiave privata creata per il servizio
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQCuivP2Vnv7s2SC\nRdMpYLIOa9+6tA+b/1VtOMG66ZZyfp6yQO+8TmC2WvjWpXI6viPnben9t77W/z11\nMec2xBOWf1RlkvSU8zzORG2A/QhtA4GChbCMo824F+SQAr+eLDEqqzb1IerhSOL3\n19aZQ3gU8p6XJtFf2JJUIq4q589aD0BOqIupHaxYhL7a+9p643AoT46FKK3InYA4\no8QuXqpZyhC4et6brhBu+zk8WwATDSdD3IT52Lc5YiLFjvdNX6ssmuOWYleZ9T67\nOsWTpAemL8KLIAyjBUnh3/uZQGxjpXYddWZsbEsJndXQc/aksrVg2vwLwxooYvP1\nBlGrSIYrAgMBAAECggEASA8MzjABSrZSsefC2EvX5tVJTgrFgPlGmut6K8EBAC7f\nNKdTcjIHgnGHVxKB2Nej+gkqN7mSu68vf8FE/BqyHYle3fpwKEhNW7jrXnvYbS0r\n3Cd2bnG33h9bGMtRsar792otK8G/dxfAwGKm8aplmnxZ1fxMJ15BdyPENOlz9PE0\n7GDPXCTmD6fo5V+p4O2pnzwYki193d96q12i5y46euAeeJh3r+U8f8pre4CXM/NT\nqHUzQO/wte7zlwb1hhvqyzg4CS4FNOaDovgbVmIl7IP7y1AfKwkrMBw/cqraty/n\nXkxLNT14re6YPThHBdIkJLk14onqOcePSx2EOfv9+QKBgQDjw7K38TzpCc1hyfR6\nAcv0Y1+TT9uk8YRzH25yHsljg3h88mYRDUCYq7NE0/F0uo0iuAjPpfQRjcmflTgD\nPCj83w/PepLnka7adJ5IQxOF5AyAX83Y4NlxoCQ7Iqm0BBpS5j+AFE/oJKd3mf2E\ns6MicZKf2XT7nPA48bq5RJnSQwKBgQDELjgpHq5yz8wrVoUC63Wcz3nGCllZNrlL\nN0PhKTy6YKXDlhoF67+4HvTBbKB0CB9vxdLec5ySRmk2mfgrpjUPIekdpGmtpcWk\nOjziwhrUOsP9l8bD+z2uwVRb1ZX+JeM64wrpG070fKd5kq0TFSafejlfLx0dYQwz\n+pQBzxhB+QKBgDb6BsqFjUlG129SOxO0GVHdJrW9IexXa7wKCzO6oKvHkS6/p8lX\n5I61ayki63ZcjTKjL2VHznjqO4+sif+l5tLa2Msg8BK7RHRwj8AriKvZ1vapqVs/\nMt1NZVFs1X+hOeVmtE8rF/qV1mJ1Jg+A+NCYj2bMK4OMZyOnnYWYvHRXAoGBAIYy\n08oVKeJyEUlIGx7/MOo+5x847xvfGmvAd1esHNWlzV746/5G4VQzINy70Rruf4q3\nOWNglKdfMRPfyWsafEtIuC3FzWCy+Hs6N3Iqs62gMXfk/lwMHorPx0Q23C8JfeJH\nc6w4OQ93whyg4HIgUtZfBqX9FZ6GR5G7BMoj/4UJAoGBAJTGrdt0/iAwVNlFNvNT\nWmvY0Z6r+nMSyO6RW5EXLgr+GGfcN3Ua/CqjxAN/eEL02OGR8vSDxhB+uc1casK/\nI1HmOIlMkSYYR54Qwn585Anr/Kxcu7yqeIRO3H/GzomD/eQQhHswsxox72ZwOLpI\nk7BKWaM99DTex0J3TZQPftul\n-----END PRIVATE KEY-----\n";

// ID del foglio elettronico dove pubblicare i dati
const char spreadsheetId[] = "1FU7t9ijq3Ch86XVjyxfLDJ3Af4fxDMHHHl0tP6y70_0";

// variabili per i timer
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;  // rileggo e invio ogni 10 secondi

// funzione di Token Callback
void tokenStatusCallback(TokenInfo info);

// imposto DHT22
#define DHTTYPE DHT22  // DHT22
uint8_t DHTPin = 4;
DHT dht(DHTPin, DHTTYPE);

// variabili per i vari sensori
float temp;
float hum;
int potenziometro;
float voltage;
float volt;

// server NTP
const char* ntpServer = "pool.ntp.org";

// salviamo epoch time
unsigned long epochTime;

// funzione per recuperare l'epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Problema sul recupero dell'ora");
    return (0);
  }
  time(&now);
  return now;
}

/* questa funzione restituisce tutte le informazioni relative al 
   collegamento con il servizio di Google */
void tokenStatusCallback(TokenInfo info) {
  if (info.status == token_status_error) {
    GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
  } else {
    GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
  }
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  pinMode(DHTPin, INPUT);
  dht.begin();

  // configurazione dell'orario
  configTime(0, 0, ntpServer);

  GSheet.printf("Versione Google Sheet Client: v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);

  // connessione al Wi-Fi
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connessione al Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* imposta il callback per lo stato di generazione del token 
     di accesso all'API di Google (solo per il debug) */
  GSheet.setTokenCallback(tokenStatusCallback);

  /* imposta i secondi per aggiornare il token di autenticazione 
     prima della scadenza (da 60 a 3540, il valore predefinito è
     300 secondi) */
  GSheet.setPrerefreshSeconds(10 * 60); 

  /* avvia la generazione del token di accesso per l'autenticazione 
     tramite Google API */
  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

void loop() {
  /* richiamo ciclicamente ready() per il continuo controllo 
     dell'autenticazione */
  bool ready = GSheet.ready();

  // lettura analogica del pin GPIO35:
  potenziometro = analogRead(35);
  voltage = map(potenziometro, 0, 4095, 0, 5.0);

  if (ready && millis() - lastTime > timerDelay) {
    lastTime = millis();

    FirebaseJson response;

    Serial.println("\nInvio dei dati come JSON:");
    Serial.println("---------------------------");

    FirebaseJson valueRange;

    // lettura dei sensori
    temp = dht.readTemperature();
    hum = dht.readHumidity();

    // lettura analogica del pin GPIO35:
    potenziometro = analogRead(35);
    voltage = map(potenziometro, 0, 4095, 0, 5.0);

    // recupero il timestamp
    epochTime = getTime();

    // imposto le colonne del foglio elettronico
    valueRange.add("majorDimension", "COLUMNS");
    valueRange.set("values/[0]/[0]", epochTime);
    valueRange.set("values/[1]/[0]", temp);
    valueRange.set("values/[2]/[0]", hum);
    valueRange.set("values/[3]/[0]", voltage);

    // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append
    // Append values to the spreadsheet
    bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "Foglio1!A1" /* range to append */, &valueRange /* data range to append */);
    if (success) {
      response.toString(Serial, true);
      valueRange.clear();
    } else {
      Serial.println(GSheet.errorReason());
    }
    Serial.println();
    Serial.println(ESP.getFreeHeap());
  }
}
