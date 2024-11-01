#include <Arduino.h>
#include <WiFi.h>
#include "Wifi.h"

String ssid;
String password;

String user = "xxxx";  // Datos del usuario
String pass = "xxxx";  // Datos del usuario

void iniciarWiFi() {
    // Intentar conectar con credenciales guardadas
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("Conectando a Wi-Fi: ");
    Serial.println(ssid);

    int max_attempts = 20;  // Máximo de intentos antes de fallo
    while (WiFi.status() != WL_CONNECTED && max_attempts-- > 0) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConectado a Wi-Fi, IP: " + WiFi.localIP().toString());
    } else {
        Serial.println("\nNo se pudo conectar a Wi-Fi.");
    }
}

void conectarWiFiManual(const char* new_ssid, const char* new_password) {
    WiFi.begin(new_ssid, new_password);
    Serial.print("Intentando conectar a la red Wi-Fi: ");
    Serial.println(new_ssid);

    int max_attempts = 20;  // Máximo de intentos
    while (WiFi.status() != WL_CONNECTED && max_attempts-- > 0) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConectado a Wi-Fi, IP: " + WiFi.localIP().toString());
    } else {
        Serial.println("\nNo se pudo conectar a la red Wi-Fi.");
    }
}

void desconectarWiFi() {
    WiFi.disconnect();
    Serial.println("Wi-Fi desconectado.");
}

void verEstadoWiFi() {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Estado de Wi-Fi: Conectado");
        Serial.println("SSID: " + WiFi.SSID());
        Serial.println("IP: " + WiFi.localIP().toString());
        Serial.println("RSSI: " + String(WiFi.RSSI()));  // Intensidad de la señal
    } else {
        Serial.println("Estado de Wi-Fi: No conectado");
    }
}
