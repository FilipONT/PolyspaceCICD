#include "unit.h"

extern Environment env;
extern App app;
extern AirConditioner acA;
extern AirConditioner acB;
extern Light lightA;
extern Sensors sensors;

// Unit
std::string Unit::getId() { return id; };
void Unit::setId(std::string id1)
{
    if (id1.length() == 4)
    {
        id = id1;
    }
    else
    {
        std::cout << "Invalid value, incorrect id format!" << std::endl;
    }
};

// Air conditioner
void AirConditioner::setDefaultTemp(int defaultValue1)
{
    sliderA.setDefaultValue(defaultValue1);
    displayA.setValue(defaultValue1);
};

void AirConditioner::setTemp(int value1)
{
    sliderA.setValue(value1);
    displayA.setValue(sliderA.getValue());
    env.setDesiredTemp(0);
};

void AirConditioner::setTempRange(int minValue1, int maxValue1)
{
    sliderA.setRange(minValue1, maxValue1);
};

int AirConditioner::getMinValue() {
    return sliderA.minValue;
};

int AirConditioner::getMaxValue() {
    return sliderA.maxValue;
};

void AirConditioner::switchOn()
{
    if (lampA.getValue() != 1)
    {
        switchA.switchOn();
        lampA.switchOn();
        env.setTempStep(0);
        env.setDesiredTemp(0);
    }
};

void AirConditioner::switchOff()
{
    if (lampA.getValue() != 0)
    {
        turnOffFan();
        switchA.switchOff();
        lampA.switchOff();
        env.setTempStep(0);
        env.setDesiredTemp(0);
    }
};

void AirConditioner::display()
{
    std::cout << name << std::endl;
    std::cout << "Temperature: ";
    if (lampA.getValue() == 1)
    {
        std::cout << displayA.getValue() << " C  ";
    }
    else
    {
        std::cout << "Offline  ";
    }
    std::cout << "Fan: ";
    if (isFanOn() == 0)
    {
        std::cout << "Off" << std::endl;
    }
    else
    {
        std::cout << "On" << std::endl;
    }
    std::cout << "\n";
};

int AirConditioner::getTemp()
{
    return displayA.getValue();
}

int AirConditioner::getTempStep()
{
    return sliderA.getStep();
};

int AirConditioner::getDefaultTemp()
{
    return sliderA.getDefaultValue();
}

void AirConditioner::turnOnFan()
{
    if (lampB.getValue() != 1 && lampA.getValue() == 1)
    {
        switchB.switchOn();
        lampB.switchOn();
        env.setTempStep(0.05);
    }
};

void AirConditioner::turnOffFan()
{
    if (lampB.getValue() != 0 && lampA.getValue() == 1)
    {
        switchB.switchOff();
        lampB.switchOff();
        env.setTempStep(-0.05);
    }
};

int AirConditioner::isFanOn()
{
    return lampB.getValue();
};

int AirConditioner::isOn()
{
    return lampA.getValue();
};

void AirConditioner::setTempStep(int step1)
{
    sliderA.setStep(step1);
};

void AirConditioner::moveTempUp()
{
    sliderA.moveUp();
    displayA.setValue(sliderA.getValue());
    env.setDesiredTemp(0);
};

void AirConditioner::moveTempDown()
{
    sliderA.moveDown();
    displayA.setValue(sliderA.getValue());
    env.setDesiredTemp(0);
};

void AirConditioner::acInterface()
{
    int option;
    int finish = 0;
    while (finish == 0)
    {
        while (!_kbhit())
        {
            updateData();
            system("CLS");
            appDisplayPanel();
            std::cout << "\n" << name << ": " << std::endl;
            std::cout << "1. Change temperature,\n2. Turn on/off the fan,\n3. Move temperature up,\n4. Move temperature down,\n5. Set temperature step,\n6. Turn on/off\n7. Go back"
                << std::endl;
            Sleep(1500);
        }
        std::cin >> option;
        switch (option)
        {
        case 1:
            std::cout << "Enter desired temperature:" << std::endl;
            int tempTemp;
            std::cin >> tempTemp;
            setTemp(tempTemp);
            break;

        case 2:
            if (isFanOn() == 0)
            {
                turnOnFan();
            }
            else
            {
                turnOffFan();
            }
            break;

        case 3:
            moveTempUp();
            break;

        case 4:
            moveTempDown();
            break;

        case 5:
            std::cout << "Enter desired step:" << std::endl;
            int option;
            std::cin >> option;
            setTempStep(option);
            break;

        case 6:
            if (isOn() == 0)
            {
                switchOn();
            }
            else
            {
                switchOff();
            }
            break;

        case 7:
            finish = 1;
            break;

        default:
            std::cout << "Invalid option!" << std::endl;
            break;
        }
    }
};

// Light
void Light::turnOn()
{
    if (lampA.getValue() != 1)
    {
        lampA.switchOn();
        env.setDesiredLight(env.getLightLevel() + getLightIntensity());
        env.setLightLevel(env.getLightLevel() + 0.9 * getLightIntensity());
    }
};

void Light::turnOff()
{
    if (lampA.getValue() != 0)
    {
        lampA.switchOff();
        env.setDesiredLight(env.getOutdoorLightLevel());
        env.setLightLevel(env.getDesiredLightLevel());
    }
};

void Light::setLightIntensity(int intensity1)
{
    int tempIntensity = getLightIntensity();
    sliderA.setValue(intensity1);
    displayA.setValue(sliderA.getValue());
};

int Light::getLightIntensity()
{
    return displayA.getValue();
};

void Light::setLightRange(int minValue1, int maxValue1)
{
    sliderA.setRange(minValue1, maxValue1);
};

int Light::getMinValue() {
    return sliderA.minValue;
};

int Light::getMaxValue() {
    return sliderA.maxValue;
};

int Light::isOn()
{
    return lampA.getValue();
};

void Light::display()
{
    std::cout << name << std::endl;
    std::cout << "Light level: ";
    if (isOn() == 1)
    {
        std::cout << getLightIntensity() << std::endl;
    }
    else
    {
        std::cout << "Offline" << std::endl;
    }
    std::cout << "\n";
};

void Light::lightInterface()
{
    int finished = 0;
    int option;
    while (finished == 0)
    {
        while (!_kbhit())
        {
            system("CLS");
            updateData(); // UPDATE
            appDisplayPanel();
            std::cout << "\n" << name << ": " << std::endl;
            std::cout << "1. Turn on/off,\n2. Set light intensity\n3. Go back\n"
                << std::endl;
            Sleep(1500);
        }
        std::cin >> option;
        switch (option)
        {
        case 1:
            if (isOn() == 0)
            {
                turnOn();
            }
            else
            {
                turnOff();
            }
            break;

        case 2:
            std::cout << "Enter desired light intensity:" << std::endl;
            std::cin >> option;
            setLightIntensity(option);
            break;

        case 3:
            finished = 1;
            break;

        default:
            std::cout << "Invalid option!" << std::endl;
            break;
        }
    }
};

//Sprinkler
void Sprinkler::turnOn()
{
    if (lampA.getValue() != 1)
    {
        lampA.switchOn();
    }
};

void Sprinkler::turnOff()
{
    if (lampA.getValue() != 0)
    {
        lampA.switchOff();
    }
};

int Sprinkler::isOn()
{
    return lampA.getValue();
};

void Sprinkler::display()
{
    // appDisplayPanel();
    std::cout << name << std::endl;
    std::cout << "Sprinkler: ";
    if (isOn() == 1)
    {
        std::cout << "Working..." << std::endl;
    }
    else
    {
        std::cout << "Offline" << std::endl;
    }
};

void Sprinkler::sprinklerInterface()
{
    int finished = 0;
    int option;
    while (finished == 0)
    {
        while (!_kbhit())
        {
            system("CLS");
            display();
            std::cout << "Sprinkler:\n1. Switch on/off\n2. Go back\n" << std::endl;
            Sleep(1500);
        }
        std::cin >> option;
        switch (option)
        {
        case 1:
            if (isOn() == 1)
            {
                turnOff();
            }
            else
            {
                turnOn();
            }
            break;

        case 2:
            finished = 1;
            break;

        default:
            std::cout << "Invalid option!" << std::endl;
            break;
        }
    }
};

//Vacuum cleaner
void AutomaticVacuum::turnOn()
{
    if (lampA.getValue() != 1)
    {
        lampA.switchOn();
    }
};

void AutomaticVacuum::turnOff()
{
    if (lampA.getValue() != 0)
    {
        lampA.switchOff();
    }
};

int AutomaticVacuum::isOn()
{
    return lampA.getValue();
};

void AutomaticVacuum::display()
{
    std::cout << name << std::endl;
    std::cout << "Automatic vacuum: ";
    if (isOn() == 1)
    {
        if (isFinished() == 1)
        {
            std::cout << "Finished, on hold" << std::endl;
        }
        else
        {
            std::cout << "Working..." << std::endl;
        }
    }
    else
    {
        std::cout << "Offline" << std::endl;
    }
};

int AutomaticVacuum::isFinished()
{
    return lampB.getValue();
};

void AutomaticVacuum::setFinished()
{
    if (lampB.getValue() == 0)
    {
        lampB.switchOn();
    }
    else
    {
        lampB.switchOff();
    }
};

void AutomaticVacuum::vacuumInterface()
{
    int finished = 0;
    int option;
    while (finished == 0)
    {
        while (!_kbhit())
        {
            system("CLS");
            display();
            std::cout << "Automatic vacuum:\n1. Switch on/off\n2. Go back\n" << std::endl;
            Sleep(1500);
        }
        std::cin >> option;
        switch (option)
        {
        case 1:
            if (isOn() == 1)
            {
                turnOff();
            }
            else
            {
                turnOn();
            }
            break;

        case 2:
            finished = 1;
            break;

        default:
            std::cout << "Invalid option!" << std::endl;
            break;
        }
    }
};

//Kettle
void Kettle::turnOn()
{
    if (lampA.getValue() != 1)
    {
        lampA.switchOn();
    }
};

void Kettle::turnOff()
{
    if (lampA.getValue() != 0)
    {
        lampA.switchOff();
    }
};

int Kettle::isOn()
{
    return lampA.getValue();
};

void Kettle::display()
{
    std::cout << name << std::endl;
    std::cout << "Kettle: ";
    if (isOn() == 1)
    {
        std::cout << "Working..." << std::endl;
    }
    else
    {
        std::cout << "Offline" << std::endl;
    }
    std::cout << "Temperature: ";
    if (waterHeatSensor.getSensorState() == 1)
    {
        std::cout << waterHeatSensor.getValue() << " -> " << displayA.getValue() << std::endl;
    }
};

int Kettle::isFinished()
{
    return lampB.getValue();
};

void Kettle::setFinished()
{
    if (lampB.getValue() == 0)
    {
        lampB.switchOn();
    }
    else
    {
        lampB.switchOff();
    }
};

int Kettle::getMinValue() {
    return sliderA.minValue;
};

int Kettle::getMaxValue() {
    return sliderA.maxValue;
};

void Kettle::setTemperature(int value1)
{
    int tempTemperature = getTemperature();
    sliderA.setValue(value1);
    displayA.setValue(sliderA.getValue());
};

int Kettle::getTemperature()
{
    return displayA.getValue();
};

void Kettle::kettleInterface()
{
    int finished = 0;
    int option;
    int option1;
    while (finished == 0)
    {
        while (!_kbhit())
        {
            system("CLS");
            display();
            std::cout << "Kettle:\n1. Switch on/off\n2. Change temperature\n3. Go back\n" << std::endl;
            Sleep(1500);
        }
        std::cin >> option;
        switch (option)
        {
        case 1:
            if (isOn() == 1)
            {
                turnOff();
            }
            else
            {
                turnOn();
            }
            break;

        case 2:
            std::cout << "Enter desired temperature: " << std::endl;
            std::cin >> option1;
            setTemperature(option1);
            break;

        case 3:
            finished = 1;
            break;

        default:
            std::cout << "Invalid option!" << std::endl;
            break;
        }
    }
};

void Kettle::initialize()
{
    turnOff();
    sliderA.maxValue = 110;
    sliderA.minValue = 0;
    waterHeatSensor.switchOn();
    waterHeatSensor.setValue(21);
    setTemperature(100);
};

void Kettle::update()
{
    if (isOn() == 1)
    {
        if (waterHeatSensor.getValue() < getTemperature())
        {
            waterHeatSensor.setValue(waterHeatSensor.getValue() + 1);
        }
        else if (waterHeatSensor.getValue() > getTemperature())
        {
            waterHeatSensor.setValue(waterHeatSensor.getValue() - 1);
        }
        else if (waterHeatSensor.getValue() == getTemperature())
        {
            system("CLS");
            std::cout << "Boiling water done!" << std::endl;
            Sleep(2000);
            turnOff();
        }
    }
    else
    {
        if (waterHeatSensor.getValue() != 21)
        {
            waterHeatSensor.setValue(waterHeatSensor.getValue() - 1);
        }
    }
};