from machine import Pin, PWM
import time

BUZZER_PIN = 18  # GPIO18

# Sequenza di note come frequenze
NOTES = [262, 196, 196, 220, 196, 1, 247, 262]

# Crea un'istanza PWM per il buzzer
buzzer = PWM(Pin(BUZZER_PIN), freq=1000, duty=0)  # Imposta duty cycle a 0 (muto)

# Funzione per eseguire una nota ad una certa frequenza
def play_tone(frequency, duration):
    buzzer.freq(frequency)  # Imposta la frequenza
    buzzer.duty(512)  # Imposta il volume al 50% (da 0 a 1023)
    time.sleep(duration)  # Attendi la durata specificata
    buzzer.duty(0)  # Spegne il suono
    time.sleep(0.2)  # Pausa tra le note

# Loop per suonare le note della sequenza
for note in NOTES:
    play_tone(note, 0.1)  # Suona ogni nota per 0.5 secondi

# Spegni il buzzer
buzzer.deinit()

