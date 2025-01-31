#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "BRAIN&BYTES";
const char* password = "Inserire_la_PASSWORD";

#define BOTtoken "7473976332:AAGkRTdYgEf0hxTy50Dx2VK0ctibCKAV8CM"
#define CHAT_ID "62466978"

// con Telegram si deve usare un certificato
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // invio certificato
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi collegato!");

  // invio messaggio
  bot.sendMessage(CHAT_ID, "Ciao, da ESP32!");
}

void loop() {}