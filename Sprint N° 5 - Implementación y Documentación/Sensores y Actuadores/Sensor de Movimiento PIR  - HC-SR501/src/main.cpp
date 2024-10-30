#include <Arduino.h>

const int pirPin = 12; // Pin donde está conectado el sensor PIR

void setup() {
    Serial.begin(115200);
    pinMode(pirPin, INPUT);
}

void loop() {
    int motionDetected = digitalRead(pirPin);
    if (motionDetected == HIGH) {
        Serial.println("Movimiento detectado!");
    } else {
        Serial.println("No hay movimiento.");
    }
    delay(2000);
}