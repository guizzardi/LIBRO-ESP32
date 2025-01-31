from machine import Pin
from time import sleep

led = Pin(32, Pin.OUT)  # Pin 32 come uscita per il LED

# Stato iniziale del LED (spento)
led_state = False

while True:
    # Cambia stato del LED
    led_state = not led_state
    led.value(led_state)
    
    # Mostra lo stato del LED nel monitor seriale
    if led_state:
        print("LED acceso")
    else:
        print("LED spento")
    
    sleep(1)
