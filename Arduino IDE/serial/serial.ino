void setup() {
  // impostiamo la velocità di connessione della UART a 115200 baud rate
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n'); // legge dalla seriale
    Serial.println("Messaggio: " + data); // stampa quanto ricevuto
  }
}