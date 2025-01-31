from machine import Pin
from time import sleep
import dht 

DHT = dht.DHT22(Pin(23))

while True:
  try:
    sleep(5) # pausa di 5 secondi prima di una rilettura
    DHT.measure()
    temp = DHT.temperature() # ricavo la temperatura
    umid = DHT.humidity() # ricavo l'umidità
    temp_f = temp * (9/5) + 32.0
    print('UMIDITA: %3.1f %%' %umid, end=" | ")
    print('TEMPERATURA: %3.1f C / %3.1f F' % (temp, temp_f))
  except OSError as e:
    print('Sensore DHT22 non trovato!')
