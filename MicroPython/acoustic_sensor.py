from machine import Pin
import time

SENSOR_PIN = 34  # GPIO34 (DAC1_6)

lastState = 1  # ultimo stato del pin
currentState = 1  # stato corrente del pin

# inizializzo il pin
sensor_pin = Pin(SENSOR_PIN, Pin.IN)

while True:
    # leggo lo stato del pin
    currentState = sensor_pin.value()

    if lastState == 1 and currentState == 0:
        print("The sound has been detected")
    elif lastState == 0 and currentState == 1:
        print("The sound has disappeared")

    # salvo l'ultimo stato
    lastState = currentState

    time.sleep(0.1)