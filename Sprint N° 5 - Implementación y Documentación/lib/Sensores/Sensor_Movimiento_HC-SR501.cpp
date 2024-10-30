#include "Sensor_Movimiento_HC-SR501.h"
#include <Arduino.h>

// Definir el pin del sensor PIR HC-SR501 (ajusta según tu conexión)
#define PIN_SENSOR_PIR 5  // Pin para el sensor PIR HC-SR501

void inicializarSensorMovimiento() {
    // Configurar el pin del sensor PIR como entrada
    pinMode(PIN_SENSOR_PIR, INPUT);
}

bool detectarMovimiento() {
    // Leer el estado del sensor PIR
    int estadoSensor = digitalRead(PIN_SENSOR_PIR);

    // El sensor PIR devuelve HIGH cuando detecta movimiento
    return estadoSensor == HIGH;
}

void setup() {
    // Inicializar el sensor de movimiento
    inicializarSensorMovimiento();
    // Configurar el puerto serie para la depuración
    Serial.begin(9600);
}

void loop() {
    // Detectar movimiento
    bool movimientoDetectado = detectarMovimiento();

    // Imprimir el estado del sensor en el puerto serie
    if (movimientoDetectado) {
        Serial.println("Movimiento detectado!");
    } else {
        Serial.println("No hay movimiento.");
    }

    // Pequeña espera para evitar lecturas demasiado rápidas
    delay(500);
}
