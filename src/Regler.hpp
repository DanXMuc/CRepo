#ifndef REGLER_HPP
#define REGLER_HPP

namespace mraa
{
	class Gpio;
}

// Der Regler reguliert den Wasserstand bzw. die Feuchtigkeit
class Regler
{
private:
	class ReglerImpl;

	int _valvePin;
	mraa::Gpio* _valveDigitalOut;

public:
	Regler(int valvePin=2);
	virtual ~Regler();

	// Öffnen und schließen des Ventils
	void openValve();
	void closeValve();

	// Ventil für Zeitspanne öffnen
	void openValveForTimeSpan(unsigned milliseconds);
};

#endif // REGLER_HPP
