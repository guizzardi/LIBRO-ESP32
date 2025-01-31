import machine
import time

trigPin = machine.Pin(5, machine.Pin.OUT)
echoPin = machine.Pin(18, machine.Pin.IN)
sound_speed = 0.034 # Impostiamo la velocità del suono

while True:
    try:
        trigPin.off() # Porto basso il trig
        time.sleep_us(2)
        trigPin.on() # Porto alto il trig per 10 us
        time.sleep_us(10)
        trigPin.off() # Poi lo riporto basso

        # Leggo il ritorno dell'impulso
        while echoPin.value() == 0:
            inizio = time.ticks_us()
        while echoPin.value() == 1:
            fine = time.ticks_us()

        durata = time.ticks_diff(fine, inizio)

        distanza = (durata * sound_speed) / 2  # Calcolo la distanza
        print('Distanza: {:.2f} Cm.'.format(distanza))
    except Exception as e:
        print('Si è verificato un errore:', e)

    time.sleep(2)
