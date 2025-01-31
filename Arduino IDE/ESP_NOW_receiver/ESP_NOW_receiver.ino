#include <esp_now.h>
#include <WiFi.h>

// buffer per il messaggio da ricevere
char receivedMessage[250];

// callback per la ricezione dei dati
void onDataReceive(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  // copia il messaggio ricevuto nel buffer
  memcpy(&receivedMessage, incomingData, sizeof(receivedMessage));
  receivedMessage[len] = '\0'; // assicurati che sia una stringa terminata da '\0'

  Serial.print("Bytes ricevuti: ");
  Serial.println(len);
  Serial.print("Messaggio: ");
  Serial.println(receivedMessage);
}

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

  // registra il callback per la ricezione dei dati
  esp_now_register_recv_cb(esp_now_recv_cb_t(onDataReceive));
}

void loop() {}

