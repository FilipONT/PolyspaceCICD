#ifndef HOUSEENVIRONMENT
#define HOUSEENVIRONMENT

#include <iostream>
#include <cstdlib>
#include "app.h"
#include "Windows.h"
#include "sensor.h"

class Environment {
private:
    float houseTemperature;
    float lightLevel;
    int concentrationCO2;
    float outdoorLightLevel;
    float outdoorTemp;
    float desiredTemp;
    float desiredLightLevel;
    int doorOpen = 0;
    int windowOpen = 0;
    float tempStep;
    int motion = 0;
public:
    float desiredTempAuto;
    float getHouseTemp();
    float getLightLevel();
    float getOutdoorLightLevel();
    float getOutdoorTemp();
    float getTempStep();
    float getDesiredTemp();
    float getDesiredLightLevel();
    int isDoorOpen();
    int isWindowOpen();
    void setHouseTemp(float temp1);
    void setTempStep(float step1);
    void setOutdoorTemp(float temp1);
    void changeTemp(float step1);
    void openDoors();
    void closeDoors();
    void openWindow();
    void closeWindow();
    void setDesiredTemp(float temp1);
    void setDesiredLight(float light1);
    void changeLightLevel(int step1);
    void setOutdoorLightLevel(float light1);
    void setLightLevel(int light1);
    int getCO2();
    void setCO2(int value1);
    void changeCO2();
    void setMotion(int value1);
    int getMotion();
};

#endif // !HOUSEENVIRONMENT