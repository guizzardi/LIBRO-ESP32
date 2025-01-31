#include "esp_sleep.h"

void setup() {
  // configura il timer RTC per risvegliare l'ESP32 dopo 10 secondi
  esp_sleep_enable_timer_wakeup(10 * 1000000);
  
  // stampa un messaggio prima di entrare in deep sleep
  Serial.begin(115200);
  Serial.println("Sto entrando in deep sleep per 10 secondi...");
  
  // Avvia il deep sleep
  esp_deep_sleep_start();
}

void loop() {
  // il codice non raggiungerà mai questa parte, dato che il chip si riavvierà al risveglio
}