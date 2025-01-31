# carica le librerie
from machine import Pin
from utime import sleep

print("Ciao, ESP32!")

# imposta LED_BUILTIN col valore 2 che corrisponde al pin GPIO2
led = Pin(2, Pin.OUT)
while True: #ciclo infinito
  led.on() # accende il LED
  sleep(1) # attende un secondo
  led.off() # spegne il LED
  sleep(1) # attende un secondo

