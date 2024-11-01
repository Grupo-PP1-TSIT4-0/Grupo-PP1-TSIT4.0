#ifndef SENSOR_AHT25_H
#define SENSOR_AHT25_H

#include <Wire.h>
#include "Adafruit_AHTX0.h"

class Sensor_Temperatura_Humedad {
public:
    Sensor_Temperatura_Humedad();
    void begin();
    float readTemperature();
    float readHumidity();

private:
    Adafruit_AHTX0 aht;
};

#endif