/*
 * Actuators.h
 *
 *  Created on: Oct 18, 2014
 *      Author: Lars
 */

#ifndef ACTUATORS_H_
#define ACTUATORS_H_

#include <time.h>
#include "Service.h"

namespace mraa
{
	class Gpio;
}

class Actuators {
public:
	Actuators(const Service& service);
	virtual ~Actuators();

	void waterPlant(int seconds);
	void checkWateringStatus();
private:
	void run();
	mraa::Gpio* Relay;
	time_t StartTime;
	int Duration;
	bool Watering;
	const Service& Servc;
};

#endif /* ACTUATORS_H_ */
