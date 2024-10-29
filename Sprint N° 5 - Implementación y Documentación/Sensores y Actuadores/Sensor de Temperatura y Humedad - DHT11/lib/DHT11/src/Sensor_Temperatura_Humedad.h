#ifndef SENSOR_DHT11_H
#define SENSOR_DHT11_H

#include <DHT.h>

class Sensor_Temperatura_Humedad {
public:
    Sensor_Temperatura_Humedad(int pin);
    void begin();
    float readTemperature();
    float readHumidity();

private:
    DHT dht;
};

#endif