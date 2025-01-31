from machine import Pin
import time

button = Pin(33, Pin.IN) # Utilizziamo GPIO33
ultimoStato = 1
prev_button_state = 0

while True:
    # Legge lo stato del pulsante
    statoCorrente = button.value()

    # Controlla se il pulsante è stato rilasciato
    if prev_button_state == 0 and statoCorrente == 1:
        print("lo stato è LOW (basso)")

    # Controlla se lo stato del pulsante è premuto
    if prev_button_state == 1 and statoCorrente == 0:
        print("lo stato è HIGH (alto)")

    # Salva lo stato per il nuovo loop
    prev_button_state = statoCorrente
