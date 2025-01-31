#include "MD_Parola.h"
#include "MD_MAX72xx.h"
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// URL Endpoint e ApiKey per le API di OpenWeather
String URL = "https://api.openweathermap.org/data/3.0/onecall?";
String ApiKey = "bf21077ac2928722a3dac7da6c690c46";

// Coordinate della città di Fermo
String lat = "43.16";
String lon = "13.72";

// Credenziali per accedere al Wi-Fi
const char* ssid = "BRAIN&BYTES";
const char* password = "********";

// Inizializzazione del server NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String orario;  // Variabile dove salvare l'orario

// Tipo di matrice di LED utilizzata
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4  // Numero di moduli LED
#define CS_PIN 5       // Pin CS

// Crea una istanza della classe MD_Parola
MD_Parola disp = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  Serial.begin(115200);
  Serial.print("Connessione a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Visualizza l'IP assegnato
  Serial.println("");
  Serial.println("Connessione al Wi-Fi riuscita.");
  Serial.println("Indirizzo IP: ");
  Serial.println(WiFi.localIP());

  // Inizializzo NTPClient per ricevere l'orario
  timeClient.begin();
  // Per impostare la timezone italiana (GMT+1) si deve aggiungere 3600:
  timeClient.setTimeOffset(3600);

  // inizializza display
  disp.begin();
  disp.setIntensity(0);
  disp.displayClear();
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    // Chiamata alle API aggiungendo all'Endpoint i dati richiesti
    http.begin(URL + "lat=" + lat + "&lon=" + lon + "&units=metric&appid=" + ApiKey);

    // Connessione e invio richiesta HTTP/GET
    int httpCode = http.GET();

    // Se non ci sono errori di connessione
    if (httpCode > 0) {

      // Lettura risposta JSON
      String JSON_Data = http.getString();
      Serial.println(JSON_Data);

      // Deserializzazione del JSON ricevuto
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, JSON_Data);
      JsonObject obj = doc.as<JsonObject>();

      // Recupero dei valori necessari
      const int pres = obj["current"]["pressure"].as<int>();
      const int temp = obj["current"]["temp"].as<int>();
      const int humi = obj["current"]["humidity"].as<int>();

      // Aggiungo le unità di misura
      String pressione = String(pres) + "hP";
      String temperatura = String(temp) + "C";
      String umidita = String(humi) + "%";

      // Fase di visualizzazione sulle matrici e sul terminale
      disp.setTextAlignment(PA_CENTER);
      disp.print(pressione);
      Serial.print("Pressione: ");
      Serial.println(pressione);
      delay(10000);
      disp.print(temperatura);
      Serial.print("Temperatura: ");
      Serial.println(temperatura);
      delay(10000);
      disp.print(umidita);
      Serial.print("Umidità: ");
      Serial.println(umidita);
      delay(10000);
    } else {
      Serial.println("Errore!");
    }

    http.end();  // Fine richiesta

    timeClient.update();  // Inizializzo richiesta al servizio NTP

    orario = timeClient.getFormattedTime();  // Estrapolo solo l'orario
    Serial.print("ORE: ");
    Serial.println(orario.substring(0, 5));  // Elimino i secondi

    disp.setTextAlignment(PA_CENTER);    // Formatto la visualizzazione centrale
    disp.print(orario.substring(0, 5));  // Visualizzo sulla matrice senza secondi

    delay(20000);
  }
}
