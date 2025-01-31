#include <DHT.h>
#define DHT22_PIN  23 // pin GPIO23 collegato al pin DATDA del DHT22

DHT dht22(DHT22_PIN, DHT22);

void setup() {
  Serial.begin(115200);
  dht22.begin(); // inizializza il sensore DHT22
}

void loop() {
  // lettura valore umidità
  float umidita  = dht22.readHumidity();
  // lettura valore temperatura in gradi Celsius
  float temperaturaC = dht22.readTemperature();
  // lettura valore temperatura in gradi Fahrenheit
  float temperaturaF = dht22.readTemperature(true);

  // controllo che la lettura dei valori sia andata a buon fine
  if ( isnan(temperaturaC) || isnan(temperaturaF) || isnan(umidita)) {
    Serial.println("Sensore DHT22 non trovato!");
  } else {
    Serial.print("UMIDITA': ");
    Serial.print(umidita);
    Serial.print("%");

    Serial.print(" | ");

    Serial.print("TEMPERATURA: ");
    Serial.print(temperaturaC);
    Serial.print("°C  ~  ");
    Serial.print(temperaturaF);
    Serial.println("°F");
  }

  // pausa di 5 secondi prima di una rilettura
  delay(5000);
}