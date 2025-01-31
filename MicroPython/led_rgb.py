from machine import Pin, PWM
from time import sleep

ROSSO = 23   # GPIO per il colore Rosso
VERDE = 22 # GPIO per il colore Verde
BLU  = 21 # GPIO per il colore Blu

red = PWM(Pin(ROSSO))
green = PWM(Pin(VERDE))
blue = PWM(Pin(BLU))

# Imposta la frequenza PWM a 1000Hz
red.freq(1000)
green.freq(1000)
blue.freq(1000)

def setColor(r, g, b):
    # Imposta il duty cycle per ogni canale
    red.duty_u16(int(r * 65535 / 255))
    green.duty_u16(int(g * 65535 / 255))
    blue.duty_u16(int(b * 65535 / 255))

while True:
    # Visualizzazione colori base
    setColor(255, 0, 0) # Rosso
    sleep(1)
    setColor(0, 255, 0) # Verde
    sleep(1)
    setColor(0, 0, 255) # Blu
    sleep(1)
    
    # Visualizzazione altri colori
    setColor(255, 255, 255) # Bianco
    sleep(1)
    setColor(255, 255, 0) # Giallo
    sleep(1)
    setColor(0, 255, 255) # Azzurro
    sleep(1)
    setColor(255, 0, 255) # Viola
    sleep(1)
    