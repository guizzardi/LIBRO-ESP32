from machine import Pin, ADC
from time import sleep

pot = ADC(Pin(34))
pot.atten(ADC.ATTN_11DB) 

while True:
  pot_value = pot.read()
  print("Valore Analogico:", str(pot_value))

  sleep(0.3)