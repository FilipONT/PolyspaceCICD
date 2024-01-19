#ifndef _UTILITIES
#define _UTILITIES

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include "unit.h"
#include "indicator.h"
#include "control.h"
#include "sensor.h"
#include "houseEnvironment.h"
#include "update.h"
#include "fileModule.h"
#include "initializeSystem.h"

struct Sensors {
    Sensor lightSensor;
	Sensor tempSensor;
    Sensor outdoorTempSensor;
	Sensor doorSensor;
	Sensor windowSensor;
    Sensor co2Sensor;
    Sensor motionSensor;
    Sensor shiftTestSensor;
};

enum State {turnOn, automatic, manual, exitApp, off};

class App {
private:
    State state;
public:
    enum State getState();
    void setState(State state1);
    void automatic();
    void manual();
    void turnOn();
    void exit();
    void off();
    void appliances();
};

void appInterface();
void appDisplayPanel();
void sensorDisplayPanel();
void displayTime();
void automaticController();
void saveData();
void initializeSystem();
float divideByGV(float var1);
void counter_func(int var1);

#endif // !_UTILITIES
