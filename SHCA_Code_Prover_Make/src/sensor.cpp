#include "sensor.h"


int Sensor::getSensorState()
{
    return sensorState;
}

void Sensor::setSensorState(int state1)
{
    if (state1 >= -1 && state1 <= 1)
    {
        sensorState = state1;
    }
    else
    {
        std::cout << "Invalid value, no such state!" << std::endl;
    }
}

float Sensor::getValue()
{
    return value;
}

void Sensor::setValue(float value1)
{
    value = value1;
}

void Sensor::switchOn()
{
    if (sensorState != -1)
    {
        sensorState = 1;
    }
}

void Sensor::switchOff()
{
    sensorState = 0;
}

void Sensor::setRange(float minValue1, float maxValue1)
{
    minValue = minValue1;
    maxValue = maxValue1;
}

void Sensor::shiftValue(int val1)
{
    val1 = val1 << 31;
    std::cout << val1 << std::endl;
}