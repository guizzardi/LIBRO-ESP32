# pagina web visualizzata come risposta
def web_page():
  html = """<!DOCTYPE HTML><html><head>
  <meta name="viewport" content="width=device-width, initial-scale=1"></head>
  <body><h2>Ciao, sono ESP32</h2></body></html>"""
  return html

import socket
import network
from time import sleep
from machine import Pin

ssid = 'BRAIN&BYTES'
password = 'vale2023'

# connessione al Wi-Fi
station = network.WLAN(network.STA_IF)
station.active(True)
station.connect(ssid, password)
 
while station.isconnected() == False:
  pass
 
print('Connesso al WiFi con successo!')
print(station.ifconfig())

# istanza socket.
# AF_INET si riferisce alla famiglia di indirizzi ipv4.
# SOCK_STREAM significa indica l'uso del protocollo TCP. 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# in ascolto sulla porta 80
s.bind(('', 80))
# numero massimo di connessioni rifiutare.
s.listen(5)

while True:
  try:
    conn, addr = s.accept() # crea un canale di connessione
    conn.settimeout(3.0)
    print('Connessione richiesta da %s' % str(addr))
    request = conn.recv(1024) # numero di byte massimo ricevibili
    conn.settimeout(None)
    request = str(request) # richiesta HTTP ricevuta
    print('Content = %s' % request)
    response = web_page() # rispondo restituendo la pagina web
    conn.send('HTTP/1.1 200 OK\n') # header della pagina web
    conn.send('Content-Type: text/html\n')
    conn.send('Connection: close\n\n')
    conn.sendall(response)
    conn.close()
  except OSError as e:
    conn.close()
    print('Connessione terminata')