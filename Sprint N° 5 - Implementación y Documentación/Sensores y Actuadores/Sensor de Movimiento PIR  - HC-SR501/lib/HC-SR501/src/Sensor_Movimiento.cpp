#include "Sensor_Movimiento.h"
#include <Arduino.h>

Sensor_Movimiento::Sensor_Movimiento(int sensorPin) : _sensorPin(sensorPin) {}

void Sensor_Movimiento::begin() {
    pinMode(_sensorPin, INPUT);
}

bool Sensor_Movimiento::detectMotion() {
    return digitalRead(_sensorPin) == HIGH;
}