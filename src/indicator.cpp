#include "indicator.h"

// Indicator
int Indicator::getIndicatorState() { return indicatorState; };
void Indicator::setIndicatorState(int state1)
{
    if (state1 >= -1 && state1 <= 2)
        {indicatorState = state1;}
    else
        {std::cout << "Invalid value, no such state!" << std::endl;}
};

// Display
void Display::setValue(int value1) { value = value1; };
void Display::setMessage(std::string message1) { message = message1; };
int Display::getValue() { return value; };
std::string Display::getMessage() { return message; };

// Lamp
void Lamp::switchOn() { value = 1; };
void Lamp::switchOff() { value = 0; };
int Lamp::getValue() { return value; };