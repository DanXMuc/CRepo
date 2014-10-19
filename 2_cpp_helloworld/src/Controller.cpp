/*
 * Controller.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: Lars
 */

#include "Controller.h"
#include "Sensors.h"
#include "algorithm"
#include "stdio.h"

namespace
{
	const unsigned int MAX_VALUES = 5;
	const float HUMIDITY_THRESHOLD = 1500.0;
}

Controller::Controller(Sensors& sensor)
	: sensor(sensor)
	, lastValues()
	, currentPos(0)
{
	lastValues.reserve(MAX_VALUES);
}

Controller::~Controller()
{
}

double Controller::average()
{
	double vals = 0;
	int valCount = (MAX_VALUES < lastValues.size() ? lastValues.size() : MAX_VALUES);
	for(int i = 0; i < valCount ; ++i)
	{
		vals += lastValues[i];
	}

	double avg = vals / valCount;
	return avg;
}

void Controller::addValue(double value)
{
	lastValues[currentPos % MAX_VALUES] = value;
	++currentPos;
}

bool Controller::necessaryToSwitchWater()
{
	addValue(sensor.humidity);
	return average() < HUMIDITY_THRESHOLD && currentPos > MAX_VALUES;
}
