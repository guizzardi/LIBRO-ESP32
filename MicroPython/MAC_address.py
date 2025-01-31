import network

# inizializza l'interfaccia di rete
wlan = network.WLAN(network.STA_IF)
# attiva la wlan
wlan.active(True)

# controlla se siamo collegati
if wlan.active():
    # recupera l'indirizzo MAC della scheda
    mac_address = wlan.config("mac")
    print(mac_address)
    print("Indirizzo MAC:", ":".join(["{:02X}".format(byte) for byte in mac_address]))
else:
    print("Wi-Fi non collegato.")