#ifndef _CONTROLDOC
#define _CONTROLDOC
#include <iostream>

class Control {
private:
    int controlState;   //-1 error, 0 inactive, 1 waiting, 2 busy
public:
    void setControlState(int state1);
    int getControlState();
    bool isControlBusy();
    bool isControlWaiting();
    bool isControlActive();
};


class Switch : public Control {
private:
    int value;
public:
    int getSwitchValue();
    void switchOn();
    void switchOff();
};

class Slider : public Control {
private:
    int step;
    int value;
    int defaultValue;
    
public:
    int maxValue;
    int minValue;
    void setRange(int minValue1, int maxValue1);
    void setStep(int step1);
    void setValue(int value1);
    void setDefaultValue(int defaultValue1);
    void moveUp();
    void moveDown();
    int getValue();
    int getStep();
    int getDefaultValue();
};
#endif // !_CONTROLDOC