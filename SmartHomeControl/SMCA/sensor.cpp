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
    // if (value1 >= minValue && value1 <= maxValue)
    // {
    //     value = value1;
    // }
    // else
    // {
    //     std::cout << "Value out of range! - Sensor" << std::endl;
    // }
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