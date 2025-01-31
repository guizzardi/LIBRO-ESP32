import network
import espnow

# Inizializza l'interfaccia Wi-Fi in modalità STA
wlan = network.WLAN(network.STA_IF)
wlan.active(True)

# Inizializza ESP-NOW
esp = espnow.ESPNow()
esp.active(True)

# Ascolto dei messaggi
try:
    while True:
        host_mac, message = esp.recv()
        if message:
            print(f"Messaggio: {message.decode('utf-8')}")
except KeyboardInterrupt:
    print("Ricezione interrotta.")