#ifndef TECLADO_H
#define TECLADO_H

#include <inttypes.h>

class Teclado
{
private:
    uint8_t filaPins[4];    // Pines de las filas
    uint8_t columnaPins[3]; // Pines de las columnas
    char keys[4][3];        // Mapeo de teclas

public:
    // Constructor
    Teclado(uint8_t fila1, uint8_t fila2, uint8_t fila3, uint8_t fila4,
            uint8_t col1, uint8_t col2, uint8_t col3);

    // Inicialización del teclado
    void iniciar();

    // Leer una tecla presionada
    char leerTecla();
};

#endif