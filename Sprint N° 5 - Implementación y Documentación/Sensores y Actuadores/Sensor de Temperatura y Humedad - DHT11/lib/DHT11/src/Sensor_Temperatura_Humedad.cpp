#include "Sensor_Temperatura_Humedad.h"

Sensor_Temperatura_Humedad::Sensor_Temperatura_Humedad(int pin) : dht(pin, DHT11) {}

void Sensor_Temperatura_Humedad::begin() {
    dht.begin();
}

float Sensor_Temperatura_Humedad::readTemperature() {
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        Serial.println("Error al leer la temperatura");
    }
    return temp;
}

float Sensor_Temperatura_Humedad::readHumidity() {
    float hum = dht.readHumidity();
    if (isnan(hum)) {
        Serial.println("Error al leer la humedad");
    }
    return hum;
}