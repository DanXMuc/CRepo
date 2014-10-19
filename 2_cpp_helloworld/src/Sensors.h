/*
 * Sensors.h
 *
 *  Created on: Oct 18, 2014
 *      Author: Lars
 */

#ifndef SENSORS_H_
#define SENSORS_H_

class Service;

namespace mraa
{
	class Aio;
	class Gpio;
}

class Sensors {
public:
	Sensors(const Service& service);
	virtual ~Sensors();

	void readSensorValues();

	double readHumidity();
	double readWater();
	double readTemperature();
	double readLight();
	bool readOverrideSwitch() const;

	double water;
	double humidity;
	double temperature;
	double light;
private:
	const Service& Servc;
	mraa::Aio* Temperature;
	mraa::Aio* Water;
	mraa::Aio* Humidity;
	mraa::Aio* Light;
	mraa::Gpio* Override;


};

#endif /* SENSORS_H_ */
