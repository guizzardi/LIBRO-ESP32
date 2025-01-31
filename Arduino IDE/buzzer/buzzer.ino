#define BUZZER 18  // GPIO18

// sequenza di note come frequenze
int melody[] = {
  262, 196, 196, 220, 196, 0, 247, 262
};

// durata delle note: 4 = un quarto, 8 = un ottavo
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  // ciclo per eseguire le note
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    // uno di tone per suonare
    tone(BUZZER, melody[thisNote], noteDuration);
    // aumento leggermente la pausa
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER);
  }
}

void loop() {}
