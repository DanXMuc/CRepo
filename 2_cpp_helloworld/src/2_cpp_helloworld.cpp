//============================================================================
// Name        : iotdk-cpp-template.cpp
// Author      : Intel Corporation
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "Service.h"
#include "Sensors.h"
#include "Actuators.h"
#include <string.h>
#include <time.h>

using namespace std;

namespace
{
	const unsigned int POLL_INTERVAL_USEC = 1000000;
	const unsigned int SAMPLE_INTERVAL = 1;
	const unsigned int DEFAULT_WATERING_TIME = 3;

	const float HUMIDITY_THRESHOLD = 1500.0;
}

bool necessaryToWaterPlant(Sensors& sensor);

int main() {
	Service s;
	s.informPlantWatered(1339);
	Sensors sensors(s);

	Actuators a(s);

	time_t readTime;
	time_t currentTime;
	time(&readTime);
	int overrideDurationFromApp;
	while(true)
	{
		bool switchState = sensors.readOverrideSwitch();
		if(switchState || necessaryToWaterPlant(sensors))
		{
			printf("watering...");
			a.waterPlant(DEFAULT_WATERING_TIME);
		}

		overrideDurationFromApp = s.readOverrideFromApp();
		printf("duration: %d\n", overrideDurationFromApp);
		if(overrideDurationFromApp != 0)
		{
			a.waterPlant(overrideDurationFromApp);
			s.acknowledgeWater();
		}
		a.checkWateringStatus();

		time(&currentTime);
		if(difftime(currentTime, readTime) > SAMPLE_INTERVAL)
		{
			sensors.readSensorValues();
			time(&readTime);
		}

		usleep(POLL_INTERVAL_USEC);
	}

	return 0;
}

bool necessaryToWaterPlant(Sensors& sensor)
{
	return sensor.humidity < HUMIDITY_THRESHOLD;
}
