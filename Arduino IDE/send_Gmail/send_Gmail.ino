#include <WiFi.h>
#include <ESP_Mail_Client.h>

#define WIFI_SSID "BRAIN&BYTES"
#define WIFI_PASSWORD "Inserire_la_PASSWORD"

#define SMTP_HOST "smtp.gmail.com"  // host SMTP

#define SMTP_PORT 465  // porta SMTP Gmail

// credenziali della mail mittente 
// (usare password app non la vera password)
#define AUTHOR_EMAIL "mittente@gmail.com"
#define AUTHOR_PASSWORD "dqig rbqr mjma gfrp"

// incirizzo del destinatario
#define RECIPIENT_EMAIL "destinatario@gmail.com"

// diciarazione per l'oggetto SMTP
SMTPSession smtp;

// dichiarazione della funzione callback per lo stato di spedizione
void smtpCallback(SMTP_Status status);

// funzione callback per lo stato di spedizione
void smtpCallback(SMTP_Status status) {
  Serial.println(status.info());  // stampa lo stato

  if (status.success()) {  // stampa il risultato della spedizione

    Serial.println("----------------");
    Serial.printf("Messaggio inviato con successo: %d\n", status.completedCount());
    Serial.printf("Messaggio inviato senza successo: %d\n", status.failedCount());
    Serial.println("----------------\n");

    for (size_t i = 0; i < smtp.sendingResult.size(); i++) {

      // memorizzo il risultato della spedizione
      SMTP_Result result = smtp.sendingResult.getItem(i);  

      Serial.printf("Messaggio Num: %d\n", i + 1);
      Serial.printf("Stato: %s\n", result.completed ? "successo" : "fallito");
      Serial.printf("Data/Ota: %s\n", MailClient.Time.getDateTimeString(result.timestamp, "%d %B %Y %H:%M:%S").c_str());
      Serial.printf("Contenuto: %s\n", result.recipients.c_str());
      Serial.printf("Oggetto: %s\n", result.subject.c_str());
    }
    Serial.println("----------------\n");

    smtp.sendingResult.clear();  // svuoto il risultato della spedizione
  }
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connessione in corso...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  MailClient.networkReconnect(true);  // imposto la riconnessione a true

  smtp.debug(1);  // imposto un debug a livello base

  // richiama la funzione di callback per avere i risultati della spedizione
  smtp.callback(smtpCallback);

  // dichiara Session_Config per le credenziali di sessione definite dall'utente
  Session_Config config;

  /* configurazione sessione */
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;

  // imposto un IP generico come host
  config.login.user_domain = F("127.0.0.1");  

  // impostazione server NTP e variabili per indicare il giusto orario
  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 1;
  config.time.day_light_offset = 0;

  SMTP_Message message; // dichiarazione della classe message

  // imposto l'header del messaggio 
  message.sender.name = F("Nome Mittente");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Messaggio di posta"; // oggetto
  message.addRecipient(F("Nome Destinatario"), RECIPIENT_EMAIL);
  message.text.content = "Ciao da ESP32.\n"; // messaggio
  message.text.transfer_encoding = "base64";  // codifica del messaggio
  message.text.charSet = F("utf-8");  // set consigliato 
  // priorità
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low; 

  // ID della email, può essere impostato a piacere
  message.addHeader(F("Message-ID: <nomemittente@gmail.com>")); 

  // connessione al server e gestione di eventuali errori
  if (!smtp.connect(&config)) {
    Serial.printf("Errore di connessione, Codice Stato: %d, Codice Errore: %d, Causa: %s\n", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    return;
  }

  if (!smtp.isLoggedIn()) {
    Serial.println("Non ancora loggato.");
  } else {
    if (smtp.isAuthenticated())
      Serial.println("Loggato con successo.");
    else
      Serial.println("Connesso senza Auth.");
  }

  // invio la mail e chiudo la sessione
  if (!MailClient.sendMail(&smtp, &message))
    Serial.printf("Errore, Codice Stato: %d, Codice Errore: %d, Causa: %s\n", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
}

void loop() {}
