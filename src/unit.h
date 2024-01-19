#ifndef _UNIT
#define _UNIT
#include <iostream>
#include "indicator.h"
#include "control.h"
#include "sensor.h"
#include "app.h"
#include "houseEnvironment.h"
#include "update.h"

class Unit {
private:
    std::string id; //4 digit id
public:
    std::string name;
    std::string getId();
    void setId(std::string id1);
};

class AirConditioner : public Unit {
private:
    Switch switchA;
    Switch switchB;
    Slider sliderA;
    Display displayA;
    Lamp lampA;
    Lamp lampB;
public:
    void setDefaultTemp(int defaultValue1);
    void setTemp(int value1);
    void setTempRange(int minValue1, int maxValue1);
    void setTempStep(int step1);
    void switchOn();
    void switchOff();
    void display();
    int getTemp();
    void turnOnFan();
    void turnOffFan();
    int isFanOn();
    int isOn();
    void moveTempUp();
    void moveTempDown();
    void acInterface();
    int getMinValue();
    int getMaxValue();
    int getDefaultTemp();
    int getTempStep();
};

class Light : public Unit {
private:
    Lamp lampA;
    Slider sliderA;
    Display displayA;
public:
    void turnOn();
    void turnOff();
    void setLightIntensity(int intensity1);
    int getLightIntensity();
    int isOn();
    void display();
    void lightInterface();
    void setLightRange(int minValue1, int maxValue1);
    friend void automaticController();
    int getMinValue();
    int getMaxValue();
};

class Sprinkler : public Unit {
private:
    Lamp lampA;
    Switch switchA;
    Display displayA;
public:
    void turnOn();
    void turnOff();
    int isOn();
    void display();
    void sprinklerInterface();
    friend void automaticController();
};

class AutomaticVacuum : public Unit {
private:
    Lamp lampA;
    Lamp lampB;
    Switch switchA;
    Display displayA;
public:
    void turnOn();
    void turnOff();
    int isOn();
    void setFinished();
    int isFinished();
    void display();
    void vacuumInterface();
    friend void automaticController();
};

class Kettle : public Unit {
private:
    Lamp lampA;
    Lamp lampB;
    Switch switchA;
    Display displayA;
    Slider sliderA;
    Sensor waterHeatSensor;
public:
    void turnOn();
    void turnOff();
    int isOn();
    void setTemperature(int value1);
    int getTemperature();
    void display();
    void kettleInterface();
    friend void automaticController();
    int getMinValue();
    int getMaxValue();
    void setFinished();
    int isFinished();
    void initialize();
    void update();
};

#endif // !_UNIT