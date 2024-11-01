#include "teclado.h"
#include <inttypes.h>

#include "Arduino.h"


// Constructor: asigna los pines a las filas y columnas
Teclado::Teclado(uint8_t fila1, uint8_t fila2, uint8_t fila3, uint8_t fila4, 
                 uint8_t col1, uint8_t col2, uint8_t col3) {
    filaPins[0] = fila1;
    filaPins[1] = fila2;
    filaPins[2] = fila3;
    filaPins[3] = fila4;
    columnaPins[0] = col1;
    columnaPins[1] = col2;
    columnaPins[2] = col3;
    
    // Mapeo de teclas del teclado matricial 4x3
    keys[0][0] = '1'; keys[0][1] = '2'; keys[0][2] = '3';
    keys[1][0] = '4'; keys[1][1] = '5'; keys[1][2] = '6';
    keys[2][0] = '7'; keys[2][1] = '8'; keys[2][2] = '9';
    keys[3][0] = '*'; keys[3][1] = '0'; keys[3][2] = '#';
}

// Inicializar los pines de filas como salida y los de columnas como entrada
void Teclado::iniciar() {
    for (int i = 0; i < 4; i++) {
        pinMode(filaPins[i], OUTPUT);
        digitalWrite(filaPins[i], HIGH);  // Configurar las filas en HIGH
    }
    for (int i = 0; i < 3; i++) {
        pinMode(columnaPins[i], INPUT_PULLUP);  // Configurar las columnas como INPUT con PULLUP
    }
}

// Leer la tecla presionada
char Teclado::leerTecla() {
    for (int fila = 0; fila < 4; fila++) {
        digitalWrite(filaPins[fila], LOW);  // Activar la fila
        for (int col = 0; col < 3; col++) {
            if (digitalRead(columnaPins[col]) == LOW) {  // Si se detecta un LOW, se presionó la tecla
                while (digitalRead(columnaPins[col]) == LOW);  // Esperar hasta que se suelte la tecla
                digitalWrite(filaPins[fila], HIGH);  // Restablecer la fila
                return keys[fila][col];  // Retorna la tecla presionada
            }
        }
        digitalWrite(filaPins[fila], HIGH);  // Restablecer la fila
    }
    return '\0';  // No se presionó ninguna tecla
}