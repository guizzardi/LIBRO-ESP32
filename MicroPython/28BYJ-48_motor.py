from machine import Pin
from time import sleep

# pin utilizzati sulla scheda
IN1 = Pin(16,Pin.OUT)
IN2 = Pin(17,Pin.OUT)
IN3 = Pin(18,Pin.OUT)
IN4 = Pin(19,Pin.OUT)

# lista dei pin
pins = [IN1, IN2, IN3, IN4]

# lista degli impulsi sui pin
mov1 = [[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]]
# lista inversa 
mov2 = [[0,0,0,1],[0,0,1,0],[0,1,0,0],[1,0,0,0]]

while True:
    for a in range(250): # esegue 250 volte
        for step in mov1: # per ogni gruppo della lista
            for i in range(len(pins)):
                pins[i].value(step[i]) # invia gli impulsi
                sleep(0.001)
    for a in range(250):
        for step in mov2:
            for i in range(len(pins)):
                pins[i].value(step[i])
                sleep(0.001)

