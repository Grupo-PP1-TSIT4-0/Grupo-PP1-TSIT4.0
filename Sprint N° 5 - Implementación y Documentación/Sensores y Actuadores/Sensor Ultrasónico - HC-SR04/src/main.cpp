#include <Arduino.h>
#include "Sensor_Ultrasonico.h"

Sensor_Ultrasonico Sensor_Ultrasonico(12, 13); // GPIO12 Trigger, GPIO13 Echo

void setup() {
    Serial.begin(115200);
    Sensor_Ultrasonico.begin();
}

void loop() {
    long distance = Sensor_Ultrasonico.readDistance();
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(2000);
}