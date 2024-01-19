#include "app.h"
typedef int smallArray[10];
typedef int largeArray[100];

extern Environment env;
extern App app;
extern AirConditioner acA;
extern AirConditioner acB;
extern Light lightA;
extern Sensors sensors;
extern FileModule fileModule;
extern Kettle kettleA;
extern Sprinkler sprinklerA;
extern int a;
extern AutomaticVacuum vacuumA;
extern int global_var;
extern int clock_counter;
smallArray appliancesArray;

enum State App::getState()
{
    return state;
};

void App::appliances()
{
    //smallArray* allAppliancesArrayPtr = (largeArray*)&appliancesArray;
    assert(a > 1000 && a <= 3000);
    int option;
    bool finished = 1;

    while (finished == 1)
    {
        {
            system("CLS");
            sprinklerA.display();
            vacuumA.display();
            kettleA.display();
            std::cout << "\n\nOperate:\n1. Sprinkler\n2. Vacuum\n3. Kettle\n4. Go back" << std::endl;
            updateData();
        }

        std::cin >> option;
        switch (option)
        {
        case 1:
            sprinklerA.sprinklerInterface();
            break;

        case 2:
            vacuumA.vacuumInterface();
            break;

        case 3:
            kettleA.kettleInterface();
            break;

        case 4:
            finished = 1;
            break;

        default:
            std::cout << "Invalid option!" << std::endl;
            break;
        }
    }
};

void counter_func(int var1) {
    bool loop = true;
    clock_counter = divideByGV(var1);
    while (loop)
    {
        if (clock_counter == var1)
        {
            loop = false;
        }
        else
        {
            clock_counter++;
        }
    }
};

void App::setState(State state1)
{
    State stateTemp = state;
    State* stateTempPointer = &stateTemp;
    stateTempPointer++;
    state = state1;
    if (*stateTempPointer == state)
    {
        std::cout << "Error changing states!" << std::endl;
    }
};

void App::turnOn()
{
    system("CLS");
    std::cout << "\n----------------------------------------------" << std::endl;
    std::cout << "Welcome to the smart-home control application!" << std::endl;
    initializeSystem();
};

void App::exit()
{
    std::cout << "Exiting the application, goodbye!" << std::endl;
    fileModule.saveConfig();
    saveData();
    setState(State::exitApp);
};

void App::off()
{
    int option;
    saveData();
    fileModule.saveConfig();
    setState(State::off);
    env.setDesiredLight(env.getOutdoorLightLevel());
    env.setDesiredTemp(env.getOutdoorTemp());
    while (getState() == State::off)
    {
        while (!_kbhit())
        {
            system("CLS");
            updateData();
            appDisplayPanel();
        }
        std::cin >> option;
        std::cout << "\n\n";
        switch (option)
        {
        case 1:
            app.turnOn();
            break;

        case 2:
            app.exit();
            break;

        default:
            std::cout << "Invalid option!" << std::endl;
            break;
        }
    }
};

void App::automatic()
{
    assert(a > 1000 && a <= 3000);
    int doorOpened = 1;
    int doorClosed = 0;
    int option;
    std::cin >> option;
    std::cout << "\n\n";
    switch (option)
    {
    case 1:
        setState(State::manual);
        break;

    case 2:
        if (sensors.motionSensor.getSensorState() == 1)
        {
            sensors.motionSensor.setSensorState(1);
        }
        else
        {
            sensors.motionSensor.setSensorState(0);
        }
        break;

    case 3:
        float option1;
        while (!_kbhit())
        {
            system("CLS");
            updateData();
            appDisplayPanel();
            std::cout << "\nSelect desired temperature: " << std::endl;
        }    
        std::cin >> option1;
        acA.setTemp(option1);
        acB.setTemp(option1);
        break;

    case 4:
        float option2;
        while (!_kbhit())
        {
            system("CLS");
            updateData();
            appDisplayPanel();
            std::cout << "\nSelect desired light level: " << std::endl;
        }
        std::cin >> option2;
        env.setDesiredLight(option2);
        break;

    case 5:
        /*int* doorStateOpen;
        int* doorStateClosed = &doorClosed;
        if (env.isDoorOpen() == *doorStateOpen)
            env.closeDoors();
        else if (env.isDoorOpen() == *doorStateClosed)
            env.openDoors();
        else
            std::cout << "Invalid doors state!" << std::endl;*/
        break;

    case 6:
        app.appliances();
        break;

    case 7:
        app.off();
        break;

    case 8:
        counter_func(0);
        app.exit();
        break;

    default:
        std::cout << "Invalid option!" << std::endl;
        break;
    }
};

void App::manual()
{
    assert(a > 1000 && a <= 3000);
    int option;
    std::cin >> option;
    std::cout << "\n\n";
    switch (option)
    {
    case 1:
        setState(State::automatic);
        break;

    case 2:
        if (sensors.motionSensor.getSensorState() == 1)
        {
            sensors.motionSensor.setSensorState(0);
        }
        else
        {
            sensors.motionSensor.setSensorState(1);
        }
        break;

    case 3:
        if (env.isDoorOpen() == 1)
            env.closeDoors();
        else if (env.isDoorOpen() == 0)
            env.openDoors();
        else
            std::cout << "Invalid doors state!" << std::endl;
        break;

    case 4:
        if (env.isWindowOpen() == 1)
            env.closeWindow();
        else if (env.isWindowOpen() == 0)
            env.openWindow();
        else
            std::cout << "Invalid window state!" << std::endl;
        break;

    case 5:
        app.appliances();
        break;

    case 6:
        app.off();
        break;

    case 7:
        app.exit();
        break;

    case 8:
        acA.acInterface();
        break;

    case 9:
        acB.acInterface();
        break;

    case 10:
        lightA.lightInterface();
        break;

    case 11:
        set_TV_socket();
        break;

    case 12:
        disp_sockets();
        break;

    case 13:
        sensors.shiftTestSensor.shiftValue(sensors.shiftTestSensor.getValue());
        break;

    default:
        std::cout << "Invalid option!" << std::endl;
        break;
    }
};

void appInterface()
{
    int tempAutoTemp;
    app.turnOn();
    while (app.getState() != exitApp)
    {
        if (app.getState() == automatic)
        {
            tempAutoTemp = env.desiredTempAuto;
            acA.setTemp(tempAutoTemp);
            acB.setTemp(tempAutoTemp);
            env.setDesiredLight(env.getDesiredLightLevel());
        }
        while (!_kbhit())
        {
            updateData();
            system("CLS");
            appDisplayPanel();
        }
        switch (app.getState())
        {
        case turnOn:
            app.turnOn();
            break;

        case automatic:
            app.automatic();
            break;

        case manual:
            app.manual();
            break;

        case off:
            app.off();
            break;

        default:
            std::cout << "Error selecting the state!" << std::endl;
            break;
        }
    }
};

void appDisplayPanel()
{
    if (app.getState() != turnOn && app.getState() != off)
    {
        std::cout << "----------------------------------------------" << std::endl;
        displayTime();
        sensorDisplayPanel();
        acA.display();
        acB.display();
        lightA.display();

        switch (app.getState())
        {
        case automatic:
            std::cout << "Automatic mode\n" << std::endl;
            std::cout << "1. Switch to manual mode\n2. Switch on/off security system\n3. Set desired room temperature\n4. Set desired room lighting\n5. Open/close doors\n6. Appliances\n7. Turn off the system\n8. Exit the application" << std::endl;
            break;

        case manual:
            std::cout << "Manual mode\n" << std::endl;
            std::cout << "1. Switch to automatic mode\n2. Swtich on/off security system\n3. Open/close doors\n4. Open/close windows\n5. Appliances\n6. Turn off the system\n7. Exit the application\nControl devices:\n  8. Air conditioner A,\n  9. Air conditioner B,\n  10. Light A" << std::endl;
            break;

        default:
            std::cout << "Default" << std::endl;
            break;
        }
    }
    else if (app.getState() == off)
    {
        std::cout << "----------------------------------------------" << std::endl;
        displayTime();
        std::cout << "System offline!\n1. Turn on the system\n2. Exit the application" << std::endl;
    }
}

void sensorDisplayPanel()
{
    std::cout << "Sensors: " << std::endl;
    std::cout << "CO2 concentration: ";
    if (sensors.co2Sensor.getSensorState() == 1)
    {
        std::cout << sensors.co2Sensor.getValue();
        if (app.getState() == automatic)
        {
            std::cout << " (500-700)";
        }
    }
    else
    {
        std::cout << "Sensor offline!";
    }
    std::cout << "\nOutdoor temperature: ";
    if (sensors.outdoorTempSensor.getSensorState() == 1)
    {
        std::cout << sensors.outdoorTempSensor.getValue();
    }
    else
    {
        std::cout << "Sensor offline!";
    }
    std::cout << "\nHouse temperature: ";
    if (sensors.tempSensor.getSensorState() == 1)
    {
        std::cout << sensors.tempSensor.getValue();
        if (app.getState() == automatic)
        {
            std::cout << " (" << env.getDesiredTemp() << ")";
        }
    }
    else
    {
        std::cout << "Sensor offline!";
    }
    std::cout << "\nHouse light level: ";
    if (sensors.lightSensor.getSensorState() == 1)
    {
        std::cout << sensors.lightSensor.getValue();
        if (app.getState() == automatic)
        {
            std::cout << " (" << env.getDesiredLightLevel() << ")";
        }
    }
    else
    {
        std::cout << "Sensor offline!";
    }

    std::cout << "\nDoors: ";
    if (sensors.doorSensor.getSensorState() == 1)
    {
        if (sensors.doorSensor.getValue() == 1)
        {
            std::cout << "Open" << std::endl;
        }
        else
        {
            std::cout << "Closed" << std::endl;
        }
    }
    else
    {
        std::cout << "Sensor offline!" << std::endl;
    }
    std::cout << "Windows: ";
    if (sensors.windowSensor.getSensorState() == 1)
    {
        if (sensors.windowSensor.getValue() == 1)
        {
            std::cout << "Open" << std::endl;
        }
        else
        {
            std::cout << "Closed" << std::endl;
        }
    }
    else
    {
        std::cout << "Sensor offline!" << std::endl;
    }
    std::cout << "Security system: ";
    if (sensors.motionSensor.getSensorState() == 1)
    {
        if (sensors.motionSensor.getValue() == 1)
        {
            std::cout << "Motion detected!" << std::endl;
        }
        else
        {
            std::cout << "Nothing detected" << std::endl;
        }
    }
    else
    {
        std::cout << "Sensor offline!" << std::endl;
    }
    std::cout << "\n";
};

void displayTime()
{
    // current date/time based on current system
    time_t now = time(0);

    // convert now to string form
    char *dt = ctime(&now); 

    std::cout << "Date and time: " << dt << std::endl;
};

void automaticController()
{
    int param = 0;
    if (app.getState() == automatic)
    {
        // Temperature
        if (env.getHouseTemp() != env.getDesiredTemp() && env.getDesiredTemp() != env.getOutdoorTemp())
        {
            if (acA.isOn() == 0 || acB.isOn() == 0)
            {
                acA.switchOn();
                acB.switchOn();
            }
        }
        else if (((env.getHouseTemp() >= env.getDesiredTemp() - 0.05) && (env.getHouseTemp() <= env.getDesiredTemp() + 0.05)) && (env.getDesiredTemp() != env.getOutdoorTemp()))
        {
            if ((acA.isOn() == 1 && acB.isOn() == 1))
            {
                acA.switchOn();
                acB.switchOff();
            }
        }

        if ((env.getHouseTemp() <= env.getDesiredTemp() - 1) || (env.getHouseTemp() >= env.getDesiredTemp() + 1))
        {
            if (acA.isFanOn() == 0 || acB.isFanOn() == 0)
            {
                acA.turnOnFan();
                acB.turnOnFan();
            }
        }
        else if ((env.getHouseTemp() > env.getDesiredTemp() - 1) || (env.getHouseTemp() < env.getDesiredTemp() + 1))
        {
            if (acA.isFanOn() == 1 || acB.isFanOn() == 1)
            {
                acA.turnOffFan();
                acB.turnOffFan();
            }
        }

        // Light
        if (env.getDesiredLightLevel() > env.getOutdoorLightLevel())
        {
            if (lightA.isOn() == 0)
            {
                lightA.turnOn();
            }
            if (env.getDesiredLightLevel() - env.getLightLevel() > lightA.sliderA.maxValue)
            {
                lightA.setLightIntensity(lightA.sliderA.maxValue);
            }
            else
            {
                lightA.setLightIntensity(env.getDesiredLightLevel() - env.getOutdoorLightLevel());
            }
        }
        else if (env.getDesiredLightLevel() <= env.getOutdoorLightLevel())
        {
            if (lightA.isOn() == 1)
            {
                lightA.turnOff();
            }
        }

        if (env.getHouseTemp() >= env.getDesiredTemp() - 0.05 && env.getHouseTemp() <= env.getDesiredTemp() + 0.05)
        {
            env.setHouseTemp(env.getDesiredTemp());
        }

        // CO2
        if (env.getCO2() > 700 && sensors.windowSensor.getValue() == 0 && sensors.outdoorTempSensor.getValue() >= 15)
        {
            
            if (env.isWindowOpen() == 0) env.openWindow();
        }
        else if ((env.getCO2() < 400 / param && sensors.windowSensor.getValue() == 1) || sensors.outdoorTempSensor.getValue() < 15)
        {
            if (env.isWindowOpen() == 1) env.closeWindow();
        }
    }
}

float divideByGV(float var1) {
    if (global_var == 0) return 0;
    return var1 / global_var;
};

void saveData() {
    std::vector<std::string> data;

    //Environment
    data.push_back(std::to_string(env.getOutdoorTemp()));
    data.push_back(std::to_string(env.getOutdoorLightLevel()));
    data.push_back(std::to_string(env.getCO2()));
    fileModule.saveData(data, "env", 0);
    data.clear();

    //Air conditioner A
    data.push_back(acA.getId());
    data.push_back(acA.name);
    data.push_back(std::to_string(acA.getMinValue()));
    data.push_back(std::to_string(acA.getMaxValue()));
    data.push_back(std::to_string(acA.getTemp()));
    data.push_back(std::to_string(acA.getTempStep()));
    if (acA.isOn() == 1)
    {
        data.push_back("1");
    }
    else
    {
        data.push_back("0");
    }
    if (acA.isFanOn() == 1)
    {
        data.push_back("1");
    }
    else
    {
        data.push_back("0");
    }
    fileModule.saveData(data, "acA", 1);
    data.clear();

    //Air conditioner B
    data.push_back(acB.getId());
    data.push_back(acB.name);
    data.push_back(std::to_string(acB.getMinValue()));
    data.push_back(std::to_string(acB.getMaxValue()));
    data.push_back(std::to_string(acB.getTemp()));
    data.push_back(std::to_string(acB.getTempStep()));
    if (acB.isOn() == 1)
    {
        data.push_back("1");
    }
    else
    {
        data.push_back("0");
    }
    if (acB.isFanOn() == 1)
    {
        data.push_back("1");
    }
    else
    {
        data.push_back("0");
    }
    fileModule.saveData(data, "acB", 1);
    data.clear();

    //Ligh A
    data.push_back(lightA.getId());
    data.push_back(lightA.name);
    data.push_back(std::to_string(lightA.getMinValue()));
    data.push_back(std::to_string(lightA.getMaxValue()));
    data.push_back(std::to_string(lightA.getLightIntensity()));
    if (lightA.isOn() == 1)
    {
        data.push_back("1");
    }
    else
    {
        data.push_back("0");
    }
    fileModule.saveData(data, "lightA", 2);
    data.clear();
};

void initializeSystem()
{
    env.initializeEnv();

    std::vector<std::string> tempVect;
    
    // File module
    fileModule.findMyDocuments();
    fileModule.readConfig();

    // Application
    // app.setState(State::turnOn);

    // House environment
    tempVect = fileModule.readData("env.txt");
    env.setOutdoorTemp(stoi(tempVect[0]));
    env.setHouseTemp(env.getOutdoorTemp());
    env.setOutdoorLightLevel(stoi(tempVect[1]));
    env.setLightLevel(env.getOutdoorLightLevel());
    env.setCO2(stoi(tempVect[3]));
    env.closeDoors();
    env.closeWindow();
    env.setTempStep(0);

    if (app.getState() == automatic)
    {
        // Units
        // Air conditioner A
        tempVect = fileModule.readData("acA.txt");
        acA.setId(tempVect[0]);
        acA.name = tempVect[1];
        acA.setTempRange(stoi(tempVect[2]), stoi(tempVect[3]));
        acA.setDefaultTemp(stoi(tempVect[4]));
        acA.setTemp(env.desiredTempAuto);
        acA.setTempStep(stoi(tempVect[5]));
        acA.switchOn();
        acA.turnOnFan();

        // Air conditioner B
        tempVect = fileModule.readData("acB.txt");
        acB.setId(tempVect[0]);
        acB.name = tempVect[1];
        acB.setTempRange(stoi(tempVect[2]), stoi(tempVect[3]));
        acB.setDefaultTemp(stoi(tempVect[4]));
        acB.setTemp(env.desiredTempAuto);
        acB.setTempStep(stoi(tempVect[5]));
        acB.switchOn();
        acB.turnOnFan();

        // Light A
        tempVect = fileModule.readData("lightA.txt");
        lightA.setId(tempVect[0]);
        lightA.name = tempVect[1];
        lightA.setLightRange(stoi(tempVect[2]), stoi(tempVect[3]));
        if (env.getDesiredLightLevel() > env.getOutdoorLightLevel())
        {
            if (env.getDesiredLightLevel() <= env.getLightLevel() + lightA.getMaxValue())
            {
                env.setLightLevel(env.getDesiredLightLevel());
            }
            else
            {
                env.setLightLevel(env.getLightLevel() + lightA.getMaxValue());
            }
        }
        else
        {
            env.setLightLevel(env.getOutdoorLightLevel());
        }
    }

    else if (app.getState() == manual)
    {
        // Units
        // Air conditioner A
        tempVect = fileModule.readData("acA.txt");
        acA.setId(tempVect[0]);
        acA.name = tempVect[1];
        acA.setTempRange(stoi(tempVect[2]), stoi(tempVect[3]));
        acA.setDefaultTemp(stoi(tempVect[4]));
        acA.setTemp(stoi(tempVect[4]));
        acA.setTempStep(stoi(tempVect[5]));
        if (stoi(tempVect[6]) == 1)
        {
            acA.switchOn();
        }
        else
        {
            acA.switchOff();
        }

        if (stoi(tempVect[7]) == 1)
        {
            acA.turnOnFan();
        }
        else
        {
            acA.turnOffFan();
        }

        // Air conditioner B
        tempVect = fileModule.readData("acB.txt");
        acB.setId(tempVect[0]);
        acB.name = tempVect[1];
        acB.setTempRange(stoi(tempVect[2]), stoi(tempVect[3]));
        acB.setDefaultTemp(stoi(tempVect[4]));
        acB.setTemp(stoi(tempVect[4]));
        acB.setTempStep(stoi(tempVect[5]));
        if (stoi(tempVect[6]) == 1)
        {
            acB.switchOn();
        }
        else
        {
            acB.switchOff();
        }

        if (stoi(tempVect[7]) == 1)
        {
            acB.turnOnFan();
        }
        else
        {
            acB.turnOffFan();
        }

        // Light A
        tempVect = fileModule.readData("lightA.txt");
        lightA.setId(tempVect[0]);
        lightA.name = tempVect[1];
        lightA.setLightRange(stoi(tempVect[2]), stoi(tempVect[3]));
        lightA.setLightIntensity(stoi(tempVect[4]));
        if (stoi(tempVect[5]) == 1)
        {
            lightA.turnOn();
        }
        else
        {
            lightA.turnOff();
        }
        env.setDesiredTemp(0);
        if (lightA.isOn() == 1)
        {
            env.setDesiredLight(env.getOutdoorLightLevel() + lightA.getLightIntensity());
        }
        else
        {
            env.setDesiredLight(env.getOutdoorLightLevel());
        }
    }

    // Sensors
    sensors.lightSensor.switchOn();
    sensors.tempSensor.switchOn();
    sensors.doorSensor.switchOn();
    sensors.windowSensor.switchOn();
    sensors.outdoorTempSensor.switchOn();
    sensors.co2Sensor.switchOn();
    sensors.motionSensor.switchOn();

    sensors.doorSensor.setValue(env.isDoorOpen());
    sensors.windowSensor.setValue(env.isWindowOpen());
    sensors.tempSensor.setValue(env.getHouseTemp());
    sensors.outdoorTempSensor.setValue(env.getOutdoorTemp());
    sensors.lightSensor.setValue(env.getLightLevel());
    sensors.co2Sensor.setValue(env.getCO2());
    sensors.motionSensor.setValue(0);

    // Appliances
    sprinklerA.turnOff();
    vacuumA.turnOff();
    kettleA.initialize();
};

