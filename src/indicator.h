#ifndef _INDICATOR
#define _INDICATOR
#include <iostream>
#include <string.h>

class Indicator {
private:
    int indicatorState; //-1 error, 0 inactive, 1 waiting, 2 busy
public:
    int getIndicatorState();
    void setIndicatorState(int state1);
};

class Display : public Indicator {
private:
    int value;
    std::string message;
public:
    // Display();
    void setValue(int value1);
    void setMessage(std::string message1);
    int getValue();
    std::string getMessage();
};

class Lamp : public Indicator {
private:
    int value;
public:
    void switchOn();
    void switchOff();
    int getValue();
};
#endif // !_INDICATOR