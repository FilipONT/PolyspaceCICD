#ifndef _FILEMODULE
#define _FILEMODULE

#include <string>
#include <filesystem>
#include <shlobj_core.h>
#include <fstream>
#include <iostream>
#include "initializeSystem.h"

class FileModule
{
private:

public:
	//std::string tempState;
	//std::filesystem::path documentsPath; // Path to user's MyDocumnets folder in native form
	//std::filesystem::directory_entry configFolder; // Info about config folder (holds path, but can hold links, etc.)
	void findMyDocuments(); // Get MyDocuments with help of Windows 
	void createConfig(); // Create a config folder
    void saveConfig(); // Save the config folder
    void readConfig(); // Read the config folder
    std::vector<std::string> readData(std::string path1); //Read data
	void saveData(std::vector<std::string> data1, std::string path1, int dataType1); //dataType1: 0 - env, 1 - ac, 2 - light
	std::string envData(std::vector<std::string> data1);
	std::string acData(std::vector<std::string> data1);
	std::string lightData(std::vector<std::string> data1);

	////
	std::string configFolderPath;
	////
};

#endif // !_FILEMODULE
