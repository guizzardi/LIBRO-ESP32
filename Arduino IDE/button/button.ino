// GPIO33 pin utilizzato per conoscere lo stato del pulsante
#define PIN_PULSANTE 33

int ultimoStato = HIGH; // lo stato precedente letto sul pin
int statoCorrente;      // lo stato attuale letto sul pin

int num = 0; // inizializza un numero progressivo

void setup() {
  Serial.begin(115200);
  // inizializzazione del pin a cui è collegato il pulsante
  // e attivazione della resistenza interna come pull up
  pinMode(PIN_PULSANTE, INPUT_PULLUP);
}

void loop() {
  // legge lo stato del pulsante
  statoCorrente = digitalRead(PIN_PULSANTE);

  if(ultimoStato == LOW && statoCorrente == HIGH) {
    Serial.print(num); // stampa a video il progressivo
    Serial.println(": lo stato è HIGH (alto)");
  } else {
    Serial.print(num); // stampa a video il progressivo
    Serial.println(": lo stato è LOW (basso)");
  }
  // salva l'ultimo stato
  ultimoStato = statoCorrente;
  num++; // incremento num
  delay(1000); // pausa di 1 secondo
}