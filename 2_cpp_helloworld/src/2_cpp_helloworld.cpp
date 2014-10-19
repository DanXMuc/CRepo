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
#include "Controller.h"
#include "Actuators.h"
#include <string.h>
#include <time.h>

#include "jhd1313m1.h"


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

    // 0x62 RGB_ADDRESS, 0x3E LCD_ADDRESS
    upm::Jhd1313m1 lcd(0, 0x3E, 0x62);


	Actuators a(s);
	Controller c(sensors);

	time_t readTime;
	time_t currentTime;
	time(&readTime);
	int overrideDurationFromApp;
	while(true)
	{
		bool switchState = sensors.readOverrideSwitch();
		if(switchState || c.necessaryToSwitchWater())
		{
			printf("watering...");
			a.waterPlant(DEFAULT_WATERING_TIME);


		    char* str = new char[16];
		    snprintf(str, 15, "Watering: %d", DEFAULT_WATERING_TIME);
		    lcd.setCursor(0,0);
		    lcd.write(str);
		}

		overrideDurationFromApp = s.readOverrideFromApp();
		printf("duration: %d\n", overrideDurationFromApp);
		if(overrideDurationFromApp != 0)
		{
		    char* str = new char[16];
		    snprintf(str, 15, "WateringApp: %d", overrideDurationFromApp);
		    lcd.setCursor(0,0);
		    lcd.write(str);

			a.waterPlant(overrideDurationFromApp);
			s.acknowledgeWater();
		}
		if(a.checkWateringStatus())
		{
		    lcd.setCursor(0,0);
		    lcd.write("               ");
		}

		time(&currentTime);
		if(difftime(currentTime, readTime) > SAMPLE_INTERVAL)
		{
			sensors.readSensorValues();

		    char* str = new char[17];
		    snprintf(str, 17, "T:%.1fC; HA:%.0f", sensors.temperature, c.average());
		    lcd.setCursor(1, 0);
		    lcd.write(str);

			time(&readTime);
		}

		usleep(POLL_INTERVAL_USEC);
	}
    lcd.close();
	return 0;
}

bool necessaryToWaterPlant(Sensors& sensor)
{
	return sensor.humidity < HUMIDITY_THRESHOLD;
}
