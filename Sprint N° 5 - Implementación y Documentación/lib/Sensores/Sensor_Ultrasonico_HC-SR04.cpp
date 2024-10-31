#include "Sensor_Ultrasonico_HC-SR04.h"
#include <Arduino.h>

// Definir los pines del HC-SR04 (ajusta según tu conexión)
#define PIN_TRIGGER 5  // Pin para el Trigger del sensor HC-SR04
#define PIN_ECHO 18    // Pin para el Echo del sensor HC-SR04

// Altura máxima del estante en cm
const int ALTURA_ESTANTE_CM = 100; // Ajusta según la altura real de tu estante

void inicializarSensorDistancia() {
    // Configurar los pines como salida para Trigger y entrada para Echo
    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    
    // Asegurarse de que el Trigger comience en LOW
    digitalWrite(PIN_TRIGGER, LOW);
    delay(50); // Pequeña espera para estabilizar el sensor
}

int leerDistanciaPaquete() {
    // Enviar un pulso de Trigger (10us en HIGH)
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);

    // Leer el tiempo que tarda el eco (en microsegundos)
    long duracionEcho = pulseIn(PIN_ECHO, HIGH);

    // Convertir la duración en distancia (cm)
    int distanciaCm = duracionEcho * 0.034 / 2; // (Velocidad del sonido: 0.034 cm/us)

    // Calcular la distancia del paquete en el estante
    int distanciaPaqueteCm = ALTURA_ESTANTE_CM - distanciaCm;

    // Asegurarse de que la distancia esté dentro de los límites del estante
    distanciaPaqueteCm = constrain(distanciaPaqueteCm, 0, ALTURA_ESTANTE_CM);

    return distanciaPaqueteCm;
}