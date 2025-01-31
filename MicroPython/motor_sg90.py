import machine
import time

# GPIO PWM utilizzato per il segnale
servoPin = machine.Pin(32, machine.Pin.OUT) 

# creazione di un oggetto per pilotare il PWM
pwm = machine.PWM(servoPin)

# impulso ogni 20ms
pwm.freq(50)

# imposta il duty cycle a 0
pwm.duty(0)

# funzione per convertire da 0 a 180 gradi in 20 a 120 PWM 
def map(x, in_min, in_max, out_min, out_max):
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

# Creates another function for turning 
# the servo according to input angle
def servo(pin, angle):
    pin.duty(map(angle, 0, 180, 20, 120))

servo(pwm, 0) # ruota il motore di 0 gradi
servo(pwm, 90) # ruota il motore di 90 gradi
servo(pwm, 180) # ruota il motore di 180 gradi

# ruota il motore da 0 a 180 gradi di 10 gradi alla volta
for i in range(0, 181, 10):
    servo(pwm, i)
    time.sleep(0.5)
    
# ruota il motore da 180 a 0 gradi di 10 gradi alla volta
for i in range(180, -1, -10):
    servo(pwm, i)
    time.sleep(0.5)