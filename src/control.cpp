#include "control.h"

// Control
void Control::setControlState(int state1)
{
    if (state1 >= -1 && state1 <= 2)
    {
        controlState = state1;
    }
    else
    {
        std::cout << "Invalid value, no such state!" << std::endl;
    }
};
int Control::getControlState() { return controlState; };
bool Control::isControlBusy()
{
    if (controlState == 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
bool Control::isControlWaiting()
{
    if (controlState == 1)
    {
        return 1;
    }
    else
    {}
};
bool Control::isControlActive()
{
    if (controlState != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

// Switch
int Switch::getSwitchValue() { return value; };
void Switch::switchOn() { value = 1; };
void Switch::switchOff() { value = 0; };

// Slider
void Slider::setRange(int minValue1, int maxValue1)
{
    minValue = minValue1;
    maxValue = maxValue1;
};
void Slider::setStep(int step1) { step = step1; };
void Slider::setValue(int value1)
{
        if (value1 >= minValue && value1 <= maxValue)
        {
            value = value1;
        }
        else
        {
            std::cout << "Invalid value, value out of range!" << std::endl;
            int state = isControlWaiting();
        }
};

void Slider::setDefaultValue(int defaultValue1)
{
    if (defaultValue1 >= minValue && value <= maxValue)
    {
        defaultValue = defaultValue1;
    }
    else
    {
        std::cout << "Invalid value, default value out of range!" << std::endl;
    }
};
void Slider::moveUp()
{
    if ((value + step) >= minValue)
    {
        value = value + step;
    }
    else
    {
        std::cout << "Invalid value, value moved out of range!" << std::endl;
    }
};
void Slider::moveDown()
{
    if ((value - step) >= minValue && (value - step) <= maxValue)
    {
        value = value - step;
    }
    else
    {
        std::cout << "Invalid value, value moved out of range!" << std::endl;
    }
};
int Slider::getValue() { return value; };
int Slider::getStep() { return step; };
int Slider::getDefaultValue() { return defaultValue; };