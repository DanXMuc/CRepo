#include "Regler.hpp"
#include "mraa/gpio.hpp"
#include "unistd.h"

using namespace mraa;

Regler::Regler(int valvePin)
	: _valvePin(valvePin)
{
	_valveDigitalOut = new mraa::Gpio(_valvePin);
	_valveDigitalOut->dir(DIR_OUT);
}

Regler::~Regler()
{
	delete _valveDigitalOut;
}

void Regler::openValve()
{
	_valveDigitalOut->write(1);
}

void Regler::closeValve()
{
	_valveDigitalOut->write(0);
}

void Regler::openValveForTimeSpan(unsigned milliseconds)
{
	openValve();
	usleep(milliseconds*1000u);
	closeValve();
}

