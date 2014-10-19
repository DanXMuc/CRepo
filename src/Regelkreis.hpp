#ifndef REGELKREIS_HPP
#define REGELKREIS_HPP

class Sollwertgeber;
class SensorInput;
class Regler;

class Regelkreis
{
private:
	Sollwertgeber* _sollwertgeber;
	SensorInput* _sensorInput;
	Regler* _regler;

	static Regelkreis* _instance;

	Regelkreis();
	~Regelkreis();

public:
	static Regelkreis* Instance();

	Sollwertgeber* getSollwertgeber() { return _sollwertgeber; }
	SensorInput* getSensorInput() { return _sensorInput; }
	Regler* getRegler() { return _regler; }
};

#endif // REGELKREIS_HPP
