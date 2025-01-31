#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

// credenziali Wi-Fi 
const char* ssid = "BRAIN&BYTES";
const char* password = "Inserire_la_PASSWORD";

// credenziali broker MQTT
const char* mqtt_broker = "6be097e457b0487987dbd7555d1e1f27.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "hivemq.webclient.1732207534150";
const char* mqtt_password = "F6$V5dW2HTbiwL1<,ra%";

// MQTT topics
const char* topic = "esp32/temp";

// pin GPIO23 dell'ESP collegato al pin DATA del DHT22
#define DHT22_PIN  23
DHT dht22(DHT22_PIN, DHT22);

// crea istanze di connessione
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

// temporizzazione
long previous_time = 0;

void setupMQTT() {
  mqttClient.setServer(mqtt_broker, mqtt_port);
}

void reconnect() {
  Serial.println("Connessione al Broker MQTT...");
  while (!mqttClient.connected()) {
    Serial.println("Riconnessione al Broker MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    // controllo la connessione
    if (mqttClient.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connesso al Broker MQTT.");
    } else {
      // in caso di fallimento stampo lo stato i riprovo
      Serial.print("Fallito, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" riprovo fra 5 secondi");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connessio al Wi-Fi");

  wifiClient.setInsecure(); // disabilita la connessione SSL

  setupMQTT(); // inizializza la connessione

  dht22.begin(); // inizializza il sensore DHT11
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  long now = millis();
  if (now - previous_time > 1000) { // Invia ogni 10 secondi
    previous_time = now;

    // lettura valore temperatura in gradi Celsius
    float temperaturaC = dht22.readTemperature();
    
    // Converte il valore in stringa
    String temp_str = String(temperaturaC);
    
    // pubblica il valore del sensore associandolo al topic
    Serial.print("Temperatura: ");
    Serial.println(temp_str);
    mqttClient.publish(topic, temp_str.c_str());
  }
}