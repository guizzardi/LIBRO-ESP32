from machine import Pin, ADC, PWM
from time import sleep

potenziometro = ADC(Pin(34)) # lettura analogica del pin GPIO34
potenziometro.width(ADC.WIDTH_10BIT) # Imposto la risoluzione a 10 bit
potenziometro.atten(ADC.ATTN_11DB) # Imposta gamma da 0 a 3.3V

led = PWM(Pin(27), 5000) # Imposto il LED sul pin 27 come PWM

while True:
    valore = potenziometro.read() # Lettura del potenziometro
    print("Valore:", str(valore))
    
    # Imposto il duty cycle uguale al valore del potenziometro
    led.duty(valore)  
    
    sleep(0.3)