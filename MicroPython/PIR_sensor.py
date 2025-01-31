from machine import Pin
from time import sleep

sensore = Pin(23, Pin.IN)

while True:
    if(sensore.value() == 0):
        print("Presenza non rilevata.")
    else:
        print("Presenza rilevata!")
    sleep(1)
