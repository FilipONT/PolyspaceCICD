#include "update.h"

extern Environment env;
extern App app;
extern AirConditioner acA;
extern AirConditioner acB;
extern Light lightA;
extern Sensors sensors;
extern Kettle kettleA;
extern int a;

void updateData() {
	automaticController();
	env.changeLightLevel(10);
	env.changeTemp(env.getTempStep());
	env.changeCO2();
	kettleA.update();
	if (sensors.doorSensor.getSensorState() == 1) sensors.doorSensor.setValue(env.isDoorOpen());
	if (sensors.windowSensor.getSensorState() == 1) sensors.windowSensor.setValue(env.isWindowOpen());
	if (sensors.tempSensor.getSensorState() == 1) sensors.tempSensor.setValue(env.getHouseTemp());
	if (sensors.outdoorTempSensor.getSensorState() == 1) sensors.outdoorTempSensor.setValue(env.getOutdoorTemp());
	if (sensors.lightSensor.getSensorState() == 1) sensors.lightSensor.setValue(env.getLightLevel());
	if (sensors.co2Sensor.getSensorState() == 1) sensors.co2Sensor.setValue(env.getCO2());
	if (sensors.motionSensor.getSensorState() == 1) sensors.motionSensor.setValue(env.getMotion());
}

void set_TV_socket() {
	char* socket1;
	char gbuffer[5], var1[11] = "Television";
	socket1 = strcpy(gbuffer, var1);
	std::cout << socket1 << std::endl;
};

void disp_sockets() {
	int sockets[4] = { 1, 2, 3, 4 };
	int i;

	for (i = 0; i <= 9; i++)
	{
		std::cout << sockets[i] << std::endl;
	}
};