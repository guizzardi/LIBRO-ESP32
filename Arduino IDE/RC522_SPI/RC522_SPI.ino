#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5    // GPIO5
#define RST_PIN 27  // GPIO27

MFRC522 rfid(SS_PIN, RST_PIN);  // inizializzo il lettore

void setup() {
  Serial.begin(115200);
  SPI.begin();      // init SPI bus
  rfid.PCD_Init();  // init MFRC522

  Serial.println("Avvicinare un tag RFID al lettore.");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {  // rilevato tag
    if (rfid.PICC_ReadCardSerial()) {  // lettura ID
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("Tipo di RFID: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));

      // stampa ID in formato esadecimale
      Serial.print("ID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();

      rfid.PICC_HaltA();       // interrompe PICC
      rfid.PCD_StopCrypto1();  // interrompe criptazione
    }
  }
}