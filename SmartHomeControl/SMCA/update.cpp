#include "update.h"

extern Environment env;
extern App app;
extern AirConditioner acA;
extern AirConditioner acB;
extern Light lightA;
extern Sensors sensors;
extern Kettle kettleA;

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