from machine import Pin
from time import sleep

# pin GPIO22 per relay 1
relay1 = Pin(22, Pin.OUT)
# pin GPIO23 per relay 2
relay2 = Pin(23, Pin.OUT)

while True:
  relay1.value(1) # apro il relay 1
  relay2.value(1) # apro il relay 2
  sleep(5)
  relay1.value(0) # chiudo il relay 1
  relay2.value(0) # chiudo il relay 2
  sleep(5)