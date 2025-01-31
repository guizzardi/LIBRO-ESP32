import bluetooth 
import ubinascii

BLE = bluetooth.BLE()
BLE.active(True)

# Nome del dispositivo da visualizzare all'accoppiamento
name = bytes("Ciao, sono ESP32", 'UTF-8')
adv_data = bytearray(b'\x02\x01\x02') + bytearray((len(name) + 1, 0x09)) + name
BLE.gap_advertise(100, adv_data)

# Ricavo l'indirizzo MAC
mac = BLE.config('mac')[1]
print("Indirizzo MAC: "+ubinascii.hexlify(mac).decode())
