#include <Wire.h>
#include <DHT.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "BRAIN&BYTES";
const char* password = "vale2023";

#define DHTTYPE DHT22  // tipologia di DHT

uint8_t DHTPin = 23;
DHT dht(DHTPin, DHTTYPE);

float temperatura;
float umidita;
int potenziometro;
int proporzione;
float volt;

AsyncWebServer server(80);  // porta del web server
AsyncEventSource events("/events");

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;  // Intervallo di lettura

String letturaDHT(const String& var) {
  // Legge l'umidità
  umidita = dht.readHumidity();
  // Legge la temperatura come Celsius (default)
  temperatura = dht.readTemperature();

  if (var == "TEMPERATURE_C") {
    return String(temperatura);
  } else if (var == "HUMIDITY") {
    return String(umidita);
  }
}

// struttura HTML della pagina web
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>WEB SERVER TEST</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Georgia; display: inline-block; text-align: center;}
    p {  font-size: 1.2rem;}
    body {  margin: 0;}
    .topnav { overflow: hidden; background-color: #4B1D3F; color: white; font-size: 1.7rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .cards { max-width: 700px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }
    .reading { font-size: 2.8rem; }
    .card.temperature { color: #ff5733; }
    .card.humidity { color: #008000; }
    .card.potenziometro { color: #0000ff; }
  </style>
</head>
<body>
  <div class="topnav">
    <h3>WEB SERVER TEST</h3>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card temperature">
        <h4><i class="fas fa-thermometer-half"></i> TEMPERATURA</h4><p><span class="reading"><span id="temp_celcius">%TEMPERATURE_C%</span> &deg;C</span></p>
      </div>
      <div class="card humidity">
        <h4><i class="fas fa-tint"></i> UMIDITA'</h4><p><span class="reading"><span id="hum">%HUMIDITY%</span> &percnt;</span></p>
      </div>
    </div>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card potenziometro">
        <h4><i class="fas fa-cog"></i> POTENZIOMETRO</h4><p><span class="reading"><span id="pot">%POTENZIOMETRO%</span> V</span></p>
      </div>
    </div>
  </div>
<script>
if (!!window.EventSource) {
 var source = new EventSource('/events');
 
 source.addEventListener('temperatura', function(e) {
  console.log("temperatura", e.data);
  document.getElementById("temp_celcius").innerHTML = e.data;
 }, false);
 
 source.addEventListener('umidita', function(e) {
  console.log("umidita", e.data);
  document.getElementById("hum").innerHTML = e.data;
 }, false);

 source.addEventListener('potenziometro', function(e) {
  console.log("potenziometro", e.data);
  document.getElementById("pot").innerHTML = e.data;
 }, false);

}
</script>
</body>
</html>)rawliteral";

void setup() {
  Serial.begin(115200);
  pinMode(DHTPin, INPUT);
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione in corso..");
  }
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // creazione del web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", index_html, letturaDHT);
  });

  // gestione degli eventi del web server
  events.onConnect([](AsyncEventSourceClient* client) {
    if (client->lastId()) {
      Serial.printf("Client ricollegato! Ultimo messaggio ID ricevuto: %u\n", client->lastId());
    }
  });
  server.addHandler(&events);
  server.begin();
}

void loop() {
  // lettura analogica del pin GPIO35
  potenziometro = analogRead(35);
  // anche se poca differenza effettuo la proporzione (0-5000 = 0V-5V)
  proporzione = map(potenziometro, 0, 4095, 0, 5000);
  // poi divido per 1000 per avere il valore effettivo
  volt = (float)proporzione / 1000;

  if ((millis() - lastTime) > timerDelay) {

    // Legge l'umidità
    umidita = dht.readHumidity();
    // Legge la temperatura come Celsius (default)
    temperatura = dht.readTemperature();

    Serial.printf("Temperatura = %.2f ºC \n", temperatura);
    Serial.printf("Umidità = %f %\n", umidita);
    Serial.print("Valore Analogico: ");
    Serial.print(volt);
    Serial.println();

    // invia eventi al web server con i valori ricevuti dai dispositivi
    events.send(String(temperatura).c_str(), "temperatura", millis());
    events.send(String(umidita).c_str(), "umidita", millis());
    events.send(String(volt).c_str(), "potenziometro", millis());

    lastTime = millis();
  }
}