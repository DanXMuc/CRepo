#ifndef SENSOR_INPUT_HPP
#define SENSOR_INPUT_HPP

#include "stdint.h"

namespace mraa {
	class Aio;
}

// SensorInput liefert die Ist-Werte der Sensoreingänge
class SensorInput
{
private:
	mraa::Aio* _humidityAnalogInput;
	mraa::Aio* _waterLevelAnalogInput;
	mraa::Aio* _temperatureAnalogInput;
	mraa::Aio* _lightAnalogInput;

	uint16_t _humidity;		// Letzter Messwert für Feuchtigkeit
	uint16_t _waterLevel;   // Letzter Messwert für Wasserstand
	uint16_t _temperature;	// Letzter Messwert für Temperatur
	uint16_t _light;		// Letzter Messwert für Licht

public:
	SensorInput(int humidityPin=1, int waterLevelPin=2, int temperaturePin=3, int lightPin=1);
	virtual ~SensorInput();

	uint16_t getHumidity() { return _humidity; }
	uint16_t getWaterLevel() { return _waterLevel; }
	uint16_t getTemperature() { return _temperature; }
	uint16_t getLight() { return _light; }

	void readSensors();
};

#endif // SENSOR_INPUT_HPP
