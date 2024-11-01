#ifndef SENSOR_MOVIMIENTO_H
#define SENSOR_MOVIMIENTO_H

class Sensor_Movimiento {
public:
    Sensor_Movimiento(int pin);
    void begin();
    bool detectMotion();

private:
    int _sensorPin;
};

#endif