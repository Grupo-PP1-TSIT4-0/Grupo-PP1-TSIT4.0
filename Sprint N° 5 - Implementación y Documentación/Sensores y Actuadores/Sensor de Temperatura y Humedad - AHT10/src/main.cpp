#include <Arduino.h>
#include "Sensor_Temperatura_Humedad.h"

Sensor_Temperatura_Humedad Sensor_Temperatura_Humedad;

void setup() {
    Serial.begin(115200);
    Sensor_Temperatura_Humedad.begin();
}

void loop() {
    float temperature = Sensor_Temperatura_Humedad.readTemperature();
    float humidity = Sensor_Temperatura_Humedad.readHumidity();

    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" °C, Humedad: ");
    Serial.println(humidity);

    delay(2000); // Espera 2 segundos antes de la siguiente lectura
}
