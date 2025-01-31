from machine import TouchPad, Pin
import time

valoreCapacitivo = 500
soglia = 200 # Valore di soglia regolabile
touch_pin = TouchPad(Pin(4)) # Pin 4 (touch_0)

while True: 
    valoreCapacitivo = touch_pin.read() # Lettura dal pin
    print("Valore sul pin: %s" % str(valoreCapacitivo))

    if valoreCapacitivo < soglia:
        print("Toccato!")
        time.sleep_ms(1000)