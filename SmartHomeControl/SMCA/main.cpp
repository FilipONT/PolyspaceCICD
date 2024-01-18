#include <iostream>
#include "indicator.h"
#include "control.h"
#include "unit.h"
#include "sensor.h"
#include "app.h"
#include "initializeSystem.h"
#include "houseEnvironment.h"
#include "fileModule.h"

Environment env;
App app;
AirConditioner acA;
AirConditioner acB;
Light lightA;
Sensors sensors;
FileModule fileModule;
Kettle kettleA;
Sprinkler sprinklerA;
AutomaticVacuum vacuumA;

int main(int argc, char *argv[])
{
	appInterface();
	return 0;
}