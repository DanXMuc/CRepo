#include "Regelkreis.hpp"
#include "Sollwertgeber.hpp"
#include "SensorInput.hpp"
#include "Regler.hpp"

Regelkreis* Regelkreis::_instance = 0;

Regelkreis::Regelkreis()
{
	_sollwertgeber = new Sollwertgeber();
	_sensorInput = new SensorInput();
	_regler = new Regler();
}

Regelkreis::~Regelkreis()
{
	delete _sollwertgeber;
	delete _sensorInput;
	delete _regler;
}

Regelkreis* Regelkreis::Instance()
{
	if (_instance == 0) _instance = new Regelkreis();
	return _instance;
}
