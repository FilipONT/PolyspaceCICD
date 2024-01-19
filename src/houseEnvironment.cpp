#include "houseEnvironment.h"

extern Environment env;
extern App app;
extern AirConditioner acA;
extern AirConditioner acB;
extern Light lightA;
extern Sensors sensors;
extern FileModule fileModule;
extern int a;


float Environment::getHouseTemp()
{
    return houseTemperature;
};

float Environment::getLightLevel()
{
    return lightLevel;
};

float Environment::getOutdoorLightLevel()
{
    return outdoorLightLevel;
};

float Environment::getOutdoorTemp()
{
    return outdoorTemp;
};

float Environment::getTempStep()
{
    return tempStep;
};

float Environment::getDesiredTemp()
{
    return desiredTemp;
};

float Environment::getDesiredLightLevel()
{
    return desiredLightLevel;
};

int Environment::isDoorOpen()
{
    if (doorOpen == 1)
        return 1;
    else
        return 0;
};

int Environment::isWindowOpen()
{
    if (windowOpen == 1)
        return 1;
    else
        return 0;
};

void Environment::setHouseTemp(float temp1)
{
    houseTemperature = temp1;
};

void Environment::setTempStep(float step1)
{
    if ((acA.isOn() == 0 && acB.isOn() == 0) || (acA.isOn() == 1 && acB.isOn() == 1))
    {
        tempStep = 0.1;
    }
    else if ((acA.isOn() == 1 && acB.isOn() == 0) || (acA.isOn() == 0 && acB.isOn() == 1))
    {
        tempStep = 0.05;
    }
    if (acA.isFanOn() == 1)
    {
        tempStep = tempStep + 0.05;
    }
    if (acB.isFanOn() == 1)
    {
        tempStep = tempStep + 0.05;
    }
    if ((getOutdoorTemp() <= getHouseTemp() && getDesiredTemp() <= getHouseTemp()) || (getOutdoorTemp() >= getHouseTemp() && getDesiredTemp() >= getHouseTemp()))
    {
        tempStep = tempStep + 0.1;
    }
    //assert(tempStep >= -0.05 && tempStep <= 0);
};

void Environment::setOutdoorTemp(float temp1)
{
    outdoorTemp = temp1;
};

void Environment::changeTemp(float step1)
{
    setTempStep(0);
    if (houseTemperature < getDesiredTemp())
    {
        if (houseTemperature != getDesiredTemp())
        {
            houseTemperature = houseTemperature + step1;
        }
    }
    else if (houseTemperature > getDesiredTemp())
    {
        if (houseTemperature != getDesiredTemp())
        {
            houseTemperature = houseTemperature - step1;
        }
    }
};

void Environment::openDoors()
{
    doorOpen = 1;
};

void Environment::closeDoors()
{
    doorOpen = 0;
};

void Environment::openWindow()
{
    windowOpen = 1;
};

void Environment::closeWindow()
{
    windowOpen = 0;
};

void Environment::setDesiredTemp(float temp1)
{
    if (temp1 == 0)
    {
        if ((acA.isOn() == 1) && (acB.isOn() == 0))
        {
            setDesiredTemp(acA.getTemp());
        }
        else if ((acA.isOn() == 0) && (acB.isOn() == 1))
        {
            setDesiredTemp(acB.getTemp());
        }
        else if ((acA.isOn() == 1) && (acB.isOn() == 1))
        {
            setDesiredTemp((acA.getTemp() + acB.getTemp()) / 2);
        }
        else
        {
            desiredTemp = getOutdoorTemp();
        }
    }
    else
    {
        desiredTemp = temp1;
    }
    
    if (app.getState() == State::automatic)
    {
        desiredTempAuto = desiredTemp;
    }
};

void Environment::setDesiredLight(float light1)
{
    desiredLightLevel = light1;
};

void Environment::changeLightLevel(int step1)
{
    if (app.getState() == State::automatic)
    {
        if (getDesiredLightLevel() <= lightLevel + lightA.getMaxValue())
        {
            if (getDesiredLightLevel() >= outdoorLightLevel)
            {
                lightLevel = getDesiredLightLevel();
            }
            else
            {
                lightLevel = outdoorLightLevel;
            }
        }
        else
        {
            lightLevel = outdoorLightLevel + lightA.getMaxValue();
        }
    }
    else
    {
        if (lightA.isOn() == 1)
        {
            lightLevel = outdoorLightLevel + lightA.getLightIntensity();
        }
    }
};

void Environment::setOutdoorLightLevel(float light1)
{
    outdoorLightLevel = light1;
};

void Environment::setLightLevel(int light1)
{
    lightLevel = light1;
};

void Environment::setCO2(int value1)
{
    if (value1 > 0 && value1 <= 10000)
    {
        concentrationCO2 = value1;
    }
    else
    {
        std::cout << "Error setting the CO2!" << std::endl;
    }
};

int Environment::getCO2()
{
    return concentrationCO2;
};

void Environment::setEmissionCoef(float coef1)
{
    emissionCoef = coef1;
};

void Environment::changeCO2()
{
    if (windowOpen == 1)
    {
        if (concentrationCO2 > 400)
        {
            concentrationCO2 = concentrationCO2 / emissionCoef;
        }
    }
    else
    {
        if (concentrationCO2 < 10000)
        {
            concentrationCO2 = concentrationCO2 + 1;
        }
    }
}

int Environment::getMotion()
{
    return motion;
};

void Environment::setMotion(int value1)
{
    if (value1 == 1 || value1 == 0)
    {
        motion = value1;
    }
}

void Environment::initializeEnv()
{
    int* emissionPTR = (int*)0x32;

    //tempStepParam = 0;
    //int* tempStepPTR = (int*)&tempStepParam;
    //*tempStepPTR = 2;

    doorOpen = 0;
    windowOpen = 0;
    motion = 0;
    emissionCoef = *emissionPTR;
};
