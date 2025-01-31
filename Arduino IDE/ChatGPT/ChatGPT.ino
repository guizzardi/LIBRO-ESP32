#include "AIChatbot.h"

AIChatbot chatbot; // Crea una instanza della classe AIChatbot

// credenziali WiFi e ChatGPT API
const char* ssid = "BRAIN&BYTES";
const char* password = "Inserire_la_PASSWORD";
const char* apiKey = "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";

void setup() {
    Serial.begin(115200); 
    chatbot.begin(115200); // comunicazione con chatbot

    // connessione al WiFi
    if (chatbot.connectWiFi(ssid, password)) {
        // invio la chiave 
        chatbot.setKey(apiKey, "chatgpt");
        // imposto il modello
        chatbot.selectAI("chatgpt", "gpt-3.5-turbo");
        Serial.println("WiFi collegato. Digitare una domanda:");
    } else {
        Serial.println("Connessione Wi-Fi fallita.");
    }
}

void loop() {
    // controllare se ci sono dati disponibili nel buffer seriale
    if (Serial.available() > 0) {
        // leggere la domanda di input dal monitor seriale
        String question = Serial.readStringUntil('\n');
        question.trim(); // rimuovi gli spazi

        // se c'è una domanda ottieni risposta da ChatGPT
        if (question.length() > 0) {
            String response = chatbot.getResponse(question);
            Serial.println("Risposta da ChatGPT: " + response);
        } else {
            Serial.println("Digita una domanda.");
        }
    }
}