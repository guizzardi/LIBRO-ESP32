#include <WiFi.h>
#include <esp_now.h>

// inizializza peer
esp_now_peer_info_t peerInfo = {};

// indirizzo MAC del dispositivo destinatario
// sostituire con l'indirizzo MAC del vostro dispositivo
uint8_t broadcastAddress[] = { 0xFC, 0xE8, 0xC0, 0xA1, 0xF0, 0x28 };

// messaggio da inviare
const char* message = "Ciao, da ESP32!";

void setup() {
  Serial.begin(115200);

  // configura la modalità Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // inizializza ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Errore inizializzazione ESP-NOW");
    return;
  }

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0; // usa il canale predefinito
  peerInfo.encrypt = false; // nessuna criptazione
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Errore nell'aggiungere il peer");
    return;
  }
}

void loop() {
  // invia il messaggio
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)message, strlen(message) + 1);

  if (result == ESP_OK) {
    Serial.println("Messaggio inviato con successo");
  } else {
    Serial.println("Errore nell'invio del messaggio");
  }

  delay(2000);
}