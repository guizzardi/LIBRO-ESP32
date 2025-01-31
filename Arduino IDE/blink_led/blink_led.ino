// imposta LED col valore 32 che corrisponde al pin GPIO32
#define LED 32

// la funzione di configurazione viene eseguita una volta,
// quando si preme reset o si alimenta la scheda
void setup() {
  // inizializza il pin digitale LED come uscita.
  pinMode(LED, OUTPUT);
}

// la funzione loop viene eseguita ciclicamente all'infinito
void loop() {
  digitalWrite(LED, HIGH);  // accende il LED (HIGH indica di fornire tensione)
  delay(1000);              // aspetta 1000 millisecondi cioè 1 secondo
  digitalWrite(LED, LOW);   // spegne il LED togliendo tensione
  delay(1000);              // aspetta 1000 millisecondi cioè 1 secondo
}