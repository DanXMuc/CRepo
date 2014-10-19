/*
 * Controller.h
 *
 *  Created on: Oct 19, 2014
 *      Author: Lars
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>

class Sensors;

class Controller {
public:
	Controller(Sensors& sensor);
	virtual ~Controller();

	bool necessaryToSwitchWater();

private:

	double average();
	void addValue(double value);
	Sensors& sensor;
	std::vector<double> lastValues;
	unsigned int currentPos;
};

#endif /* CONTROLLER_H_ */
