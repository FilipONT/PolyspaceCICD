#ifndef _SENSOR
#define _SENSOR
#include <iostream>


class Sensor {
private:
    int sensorState; //-1 error, 0 inactive, 1 active
    float value;
    float maxValue;
    float minValue;
public:
    void setSensorState(int state1);
    int getSensorState();
    float getValue();
    void setValue(float value1);
    void switchOn();
    void switchOff();
    void setRange(float minValue1, float maxValue1);
};

#endif // !_SENSOR