#include "Sensor_Temperatura_Humedad.h"

Sensor_Temperatura_Humedad::Sensor_Temperatura_Humedad() {}

void Sensor_Temperatura_Humedad::begin() {
    if (!aht.begin()) {
        Serial.println("AHT25 no encontrado");
    }
}

float Sensor_Temperatura_Humedad::readTemperature() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    return temp.temperature;
}

float Sensor_Temperatura_Humedad::readHumidity() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    return humidity.relative_humidity;
}