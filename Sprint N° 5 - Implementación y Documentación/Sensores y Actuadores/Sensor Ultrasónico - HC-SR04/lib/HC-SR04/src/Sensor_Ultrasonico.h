#ifndef SENSOR_ULTRASONICO_H
#define SENSOR_ULTRASONICO_H

class Sensor_Ultrasonico {
public:
    Sensor_Ultrasonico(int triggerPin, int echoPin);
    void begin();
    long readDistance();

private:
    int _triggerPin;
    int _echoPin;
};

#endif