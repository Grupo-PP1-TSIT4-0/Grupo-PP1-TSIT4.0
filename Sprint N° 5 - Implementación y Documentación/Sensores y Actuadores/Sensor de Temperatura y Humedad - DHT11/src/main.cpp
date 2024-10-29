#include <Arduino.h>
#include "Sensor_Temperatura_Humedad.h"

Sensor_Temperatura_Humedad Sensor_Temperatura_Humedad(14); // GPIO14

void setup() {
    Serial.begin(115200);
    Sensor_Temperatura_Humedad.begin();
}

void loop() {
    float temperature = Sensor_Temperatura_Humedad.readTemperature();
    float humidity = Sensor_Temperatura_Humedad.readHumidity();

    // Manejo de errores
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error al leer del sensor DHT11");
    } else {
        Serial.print("Temperatura: ");
        Serial.print(temperature);
        Serial.print(" °C, Humedad: ");
        Serial.println(humidity);
    }

    delay(2000);
}