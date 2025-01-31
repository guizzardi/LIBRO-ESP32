from machine import ADC, Pin
import time

# inizializza ADC GIOP34 (ADC1_6)
adc = ADC(Pin(34)) 
# imposta la risoluzione a 12 bits
adc.width(ADC.WIDTH_12BIT)
# imposto l'attenuazione a 11 dB (~3.3V input)
adc.atten(ADC.ATTN_11DB)

while True:
    # lettura del valore analogico (compreso tra 0 e 4095)
    value = adc.read() 

    if value < 40:
        description = " => Luce diretta"
    elif value < 800:
        description = " => Luminoso"
    elif value < 2000:
        description = " => Luce"
    elif value < 3200:
        description = " => Penombra"
    else:
        description = "=> Buio"

    print(f"Luminosità: {value} {description}")

    time.sleep(0.5) 