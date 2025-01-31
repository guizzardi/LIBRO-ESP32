// imposta LED_BUILTIN col valore 2 che corrisponde al pin GPIO2
#define LED_BUILTIN 2 

// la funzione di configurazione viene eseguita una volta,
// quando si preme reset o si alimenta la scheda
void setup() {
  // inizializza il pin digitale LED_BUILTIN come uscita.
  pinMode(LED_BUILTIN, OUTPUT);
}

// la funzione loop viene eseguita ciclicamente all'infinito
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // accende il LED (HIGH indica di fornire tensione)
  delay(1000);                      // aspetta 1000 millisecondi cioè 1 secondo
  digitalWrite(LED_BUILTIN, LOW);   // spegne il LED togliendo tensione
  delay(1000);                      // aspetta 1000 millisecondi cioè 1 secondo
}
