#ifndef SOLLWERTGEBER_HPP
#define SOLLWERTGEBER_HPP

#include "stdint.h"

// Der Sollwertgeber liefert die Sollwerte für die Sensoreingänge
class Sollwertgeber
{
private:
	uint16_t _humidity;
	uint16_t _waterLevel;

public:
	Sollwertgeber() : _humidity(0), _waterLevel(0) {}

	// Sollwert Feuchtigkeitssensor
	uint16_t getHumidity() { return _humidity; }
	void setHumidity(uint16_t humidity) { _humidity = humidity; }

	// Sollwert Wasserstandssensor
	uint16_t getWaterLevel() { return _waterLevel; }
	void setWaterLevel(uint16_t waterLevel) { _waterLevel = waterLevel; }
};

#endif // SOLLWERTGEBER_HPP
