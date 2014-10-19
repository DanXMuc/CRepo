#include "SensorInput.hpp"
#include "mraa/aio.hpp"

using namespace mraa;

SensorInput::SensorInput(int humidityPin, int waterLevelPin, int temperaturePin, int lightPin)
	: _humidity(0)
	, _waterLevel(0)
	, _temperature(0)
	, _light(0)
{
	_humidityAnalogInput = new Aio(humidityPin);
	_waterLevelAnalogInput = new Aio(waterLevelPin);
	_temperatureAnalogInput = new Aio(temperaturePin);
	_lightAnalogInput = new Aio(lightPin);
}

SensorInput::~SensorInput()
{
	delete _humidityAnalogInput;
	delete _waterLevelAnalogInput;
	delete _temperatureAnalogInput;
	delete _lightAnalogInput;
}

void SensorInput::readSensors()
{
	_humidity = _humidityAnalogInput->read();
	_waterLevel = _waterLevelAnalogInput->read();
	_temperature = _temperatureAnalogInput->read();
	_light = _lightAnalogInput->read();
}
