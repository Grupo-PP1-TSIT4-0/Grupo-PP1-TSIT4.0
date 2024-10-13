#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "wifi.h"

const char* ssid = "Power_Rangers";        // Nombre de la red Wi-Fi
const char* password = "PowerRangersForceInnovation";  // Contraseña de la red Wi-Fi

String user = "PowerRangers";
String pass = "PowerRangersForceInnovation";

void iniciarWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando a Wi-Fi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado a Wi-Fi, IP: " + WiFi.localIP().toString());
}

void manejarWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String datos_a_enviar = "?user=" + user + "&pass=" + pass;
    
    http.begin("http://www.powerragersforceinnovation.com/php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int codigo_respuesta = http.POST(datos_a_enviar);

    if (codigo_respuesta > 0) {
      Serial.println("Código HTTP: " + String(codigo_respuesta));
      if (codigo_respuesta == HTTP_CODE_OK) {
        String respuesta = http.getString();
        Serial.println("Respuesta del servidor: " + respuesta);
      }
    } else {
      Serial.println("Error en la conexión HTTP.");
    }
    http.end();
  } else {
    Serial.println("No conectado a Wi-Fi.");
  }

  delay(2000);  // Evitar spam excesivo de peticiones
}
