const int rosso = 23;  // GPIO per il colore Rosso
const int verde = 22;  // GPIO per il colore Verde
const int blu = 21;  // GPIO per il colore Blu

void setup() {
  pinMode(rosso, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(blu, OUTPUT);
}

void loop() {
  // visualizzazione colori base
  setColor(255, 0, 0); // Rosso
  delay(1000);
  setColor(0, 255, 0); // Verde
  delay(1000);
  setColor(0, 0, 255); // Blu
  delay(1000);

  // visualizzazione altri colori 
  setColor(255, 255, 255); // Bianco
  delay(1000);
  setColor(255, 255, 0); // Giallo
  delay(1000);
  setColor(0, 255, 255); // Azzurro
  delay(1000);
  setColor(255, 0, 255); // Viola
  delay(1000);
}

void setColor(int ValoreRosso, int ValoreVerde, int ValoreBlu) {
  analogWrite(rosso, ValoreRosso);  // invia il valore del Rosso
  analogWrite(verde, ValoreVerde);  // invia il valore del Verde
  analogWrite(blu, ValoreBlu);  // invia il valore del Blu
}