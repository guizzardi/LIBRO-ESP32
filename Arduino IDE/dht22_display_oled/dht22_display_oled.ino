#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHT11_PIN  23 // pin GPIO23 dell'ESP collegato al pin DATDA del DHT11

DHT dht11(DHT11_PIN, DHT11);

#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(9600);
  dht11.begin(); // inizializza il sensore DHT11
}

void loop() {
  // lettura valore umidità
  float umidita  = dht11.readHumidity();
  // lettura valore temperatura in gradi Celsius
  float temperaturaC = dht11.readTemperature();
  // lettura valore temperatura in gradi Fahrenheit
  float temperaturaF = dht11.readTemperature(true);

  // controllo che la lettura dei valori sia andata a buon fine
  if ( isnan(temperaturaC) || isnan(temperaturaF) || isnan(umidita)) {
    Serial.println("Sensore DHT11 non trovato!");
  } else {
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);

    display.print("U: ");
    display.print(umidita);
    display.println("%");
    display.print("T: ");
    display.print(temperaturaC);
    display.println("C");
    display.print("T: ");
    display.print(temperaturaF);
    display.print("F");
    display.display();
 
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