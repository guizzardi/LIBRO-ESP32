#include "BluetoothSerial.h"

BluetoothSerial ESP_BT;
uint8_t MAC_Address[6];
String mac_str;  // stringa a cui sarà assegnato il MAC

void setup() {
  Serial.begin(115200);

  // nome del dispositivo da visualizzare all'accoppiamento
  ESP_BT.begin("Ciao, sono ESP32");

  mac_str = ESP_BT.getBtAddressString();  // recupero il MAC
  Serial.print("Indirizzo MAC: ");
  Serial.println(mac_str.c_str());
}

void loop() {
  if (Serial.available()) {
    ESP_BT.write(Serial.read());
  }
  if (ESP_BT.available()) {
    Serial.write(ESP_BT.read());
  }
  delay(20);
}