#include "fileModule.h"

extern Environment env;
extern App app;
extern AirConditioner acA;
extern AirConditioner acB;
extern Light lightA;
extern Sensors sensors;
extern FileModule fileModule;

void FileModule::findMyDocuments() {
    PWSTR ppszPath;     //variable to receive the path memory block pointer
    HRESULT hR = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &ppszPath);  //Get the known folder path pointer
    std::filesystem::path documentsPath = ppszPath; //copy the path
    CoTaskMemFree(ppszPath);    //free memory block
    std::filesystem::directory_entry temp1{ documentsPath / "SmartHomeControl\\Config" };
    configFolder = temp1;
    if (!std::filesystem::exists(configFolder))
    {
        createConfig();
    }
};

void FileModule::createConfig() {
    std::filesystem::create_directories(configFolder);
    std::filesystem::path tempPath = configFolder.path() / "config.txt";
    std::ofstream File(tempPath);
    File << "DesiredTemperature(C): " << "26" << std::endl 
         << "DesiredLightLevel(lm): " << "1000" << std::endl
         << "Mode: " << "automatic" << std::endl;
    File.close();
};

void FileModule::saveConfig() {
    std::filesystem::path tempPath = configFolder.path() / "config.txt";
    std::ofstream File(tempPath);
    if (app.getState() == State::automatic)
    {
        tempState = "automatic";
    }
    else if (app.getState() == State::manual)
    {
        tempState = "manual";
    }
    File << "DesiredTemperature(C): " << env.desiredTempAuto << std::endl 
         << "DesiredLightLevel(lm): " << env.getDesiredLightLevel() << std::endl
         << "Mode: " << tempState << "\n" << std::endl;
    File.close();
};

void FileModule::readConfig() {
    std::string line;
    std::vector<std::string> tempVect;
    std::ifstream File(configFolder.path() / "config.txt");
    if (File.is_open())
    {
        while (true)
        {
            File.ignore(10000, ' ');
            std::getline(File, line);
            if (File.eof())
            {
                break;
            }
            else
            {
                tempVect.push_back(line);
            }
        }
    }
    else
    {
        std::cout << "Error opening the config file!" << std::endl;
    }
    File.close();

    env.setDesiredTemp(stoi(tempVect[0]));
    env.desiredTempAuto = (stoi(tempVect[0]));
    env.setDesiredLight(stoi(tempVect[1]));
    if (tempVect[2] == "automatic")
    {
        app.setState(State::automatic);
    }
    else if (tempVect[2] == "manual")
    {
        app.setState(State::manual);
    }
};

std::vector<std::string> FileModule::readData(std::string path1) {
    std::string line;
    std::vector<std::string> tempVect;
    std::ifstream File(configFolder.path() / path1);
    if (File.is_open())
    {
        while (true)
        {
            File.ignore(10000, ' ');
            std::getline(File, line);
            if (File.eof())
            {
                break;
            }
            else
            {
                tempVect.push_back(line);
            }
        }
    }
    else
    {
        std::cout << "Error opening the file!" << std::endl;
    }
    File.close();
    return tempVect;
};

void FileModule::saveData(std::vector<std::string> data1, std::string path1, int dataType1) {
    std::string fileData;
    path1 = path1 + ".txt";
    switch (dataType1)
    {
    case 0:
        fileData = fileModule.envData(data1);
        break;

    case 1:
        fileData = fileModule.acData(data1);
        break;

    case 2:
        fileData = fileModule.lightData(data1);
        break;
    }
    std::filesystem::path tempPath = configFolder.path() / path1;
    std::ofstream File(tempPath);
    File << fileData << std::endl;
    File.close();
};

std::string FileModule::envData(std::vector<std::string> data1) {
    std::string tempData = "OutdoorTemp: " + data1[0] + "\nOutdoorLightLevel: " + data1[1] + "\nCO2Level: " + data1[2];
    return tempData;
};

std::string FileModule::acData(std::vector<std::string> data1) {
    std::string tempData = "Id: " + data1[0] + "\nName: " + data1[1] + "\nMinValue: " + data1[2] + "\nMaxValue: " + data1[3] + "\nTemp: " + data1[4] + "\nTempStep: " + data1[5] + "\nIsOn: " + data1[6] + "\nIsFanOn: " + data1[7];
    return tempData;
};

std::string FileModule::lightData(std::vector<std::string> data1) {
    std::string tempData = "Id: " + data1[0] + "\nName: " + data1[1] + "\nMinValue: " + data1[2] + "\nMaxValue: " + data1[3] + "\nLightIntensity: " + data1[4] + "\nIsOn: " + data1[5];
    return tempData;
};