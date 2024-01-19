#include "initializeSystem.h"

extern Environment env;
extern App app;
extern AirConditioner acA;
extern AirConditioner acB;
extern Light lightA;
extern Sensors sensors;
extern FileModule fileModule;

//void initializeSystem()
//{
//    std::vector<std::string> tempVect;
//    fileModule.findMyDocuments();
//    // Application
//    // app.setState(State::turnOn);
//
//    // House environment
//    tempVect = fileModule.readData("env.txt");
//    env.setOutdoorTemp(stoi(tempVect[0]));
//    env.setHouseTemp(env.getOutdoorTemp());
//    env.setOutdoorLightLevel(stoi(tempVect[1]));
//    env.setLightLevel(env.getOutdoorLightLevel());
//    env.setDesiredLight(env.getLightLevel());
//    env.setDesiredTemp(env.getOutdoorTemp());
//    env.closeDoors();
//    env.closeWindow();
//    env.setTempStep(0);
//
//    // Units
//    // Air conditioner A
//    tempVect = fileModule.readData("acA.txt");
//    acA.setId(tempVect[0]);
//    acA.name = tempVect[1];
//    acA.setTempRange(stoi(tempVect[2]), stoi(tempVect[3]));
//    acA.setDefaultTemp(stoi(tempVect[4]));
//    acA.setTemp(stoi(tempVect[4]));
//    acA.setTempStep(stoi(tempVect[5]));
//    if (stoi(tempVect[6]) == 1)
//    {
//        acA.switchOn();
//    }
//    else
//    {
//        acA.switchOff();
//    }
//
//    if (stoi(tempVect[7]) == 1)
//    {
//        acA.turnOnFan();
//    }
//    else
//    {
//        acA.turnOffFan();
//    }
//
//    // Air conditioner B
//    tempVect = fileModule.readData("acB.txt");
//    acB.setId(tempVect[0]);
//    acB.name = tempVect[1];
//    acB.setTempRange(stoi(tempVect[2]), stoi(tempVect[3]));
//    acB.setDefaultTemp(stoi(tempVect[4]));
//    acB.setTemp(stoi(tempVect[4]));
//    acB.setTempStep(stoi(tempVect[5]));
//    if (stoi(tempVect[6]) == 1)
//    {
//        acB.switchOn();
//    }
//    else
//    {
//        acB.switchOff();
//    }
//
//    if (stoi(tempVect[7]) == 1)
//    {
//        acB.turnOnFan();
//    }
//    else
//    {
//        acB.turnOffFan();
//    }
//    
//    // Light A
//    tempVect = fileModule.readData("lightA.txt");
//    lightA.setId(tempVect[0]);
//    lightA.name = tempVect[1];
//    lightA.setLightRange(stoi(tempVect[2]), stoi(tempVect[3]));
//    lightA.setLightIntensity(stoi(tempVect[4]));
//    lightA.turnOn();
//
//    // Sensors
//    sensors.lightSensor.switchOn();
//    sensors.tempSensor.switchOn();
//    sensors.doorSensor.switchOn();
//    sensors.windowSensor.switchOn();
//    sensors.outdoorTempSensor.switchOn();
//    
//    sensors.doorSensor.setValue(env.isDoorOpen());
//    sensors.windowSensor.setValue(env.isWindowOpen());
//    sensors.tempSensor.setValue(env.getHouseTemp());
//    sensors.outdoorTempSensor.setValue(env.getOutdoorTemp());
//    sensors.lightSensor.setValue(env.getLightLevel());
//};
