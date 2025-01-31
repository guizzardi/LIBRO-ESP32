import network
import espnow
import time

# Inizializza l'interfaccia Wi-Fi in modalità STA
wlan = network.WLAN(network.STA_IF)
wlan.active(True)

# Inizializza ESP-NOW
esp = espnow.ESPNow()
esp.active(True)

# Sostituisci con l'indirizzo MAC del ricevitore
peer_mac = b'\xFC\xE8\xC0\xA1\xF0\x28'
esp.add_peer(peer_mac)

# Invio messaggi
try:
    while True:
        message = "Ciao, da ESP32!"
        esp.send(peer_mac, message.encode('utf-8'))
        print("Messaggio inviato:", message)
        time.sleep(3)
except KeyboardInterrupt:
    print("Trasmissione interrotta.")
    