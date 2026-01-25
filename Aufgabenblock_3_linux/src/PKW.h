/*
 * PKW.h
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */

#ifndef PKW_H_
#define PKW_H_

#include <iostream>
#include <limits>
#include <string>

#include "Fahrzeug.h"

class PKW: public Fahrzeug {
private:
	double p_dVerbrauch;    // L/100km
	double p_dTankvolumen;  // L
	double p_dTankinhalt;   // L

public:
	PKW(const std::string &name, double vmax, double verbrauch, double tankvol =
			55.0);
	//virtual ~PKW()

	double dTanken(double dMenge = std::numeric_limits<double>::infinity())
			override;
	void vSimulieren() override;
	static void vKopf();
	void vAusgeben(std::ostream &os = std::cout) const override;

	double dGeschwindigkeit() const override;

	double getTankinhalt() const; // FIXME consider renaming
	double dTankvolumen() const;

	void vZeichnen(const Weg &weg) const override;

	void vEinlesen(std::istream &in, bool bMitGrafik ) override {
		Fahrzeug::vEinlesen(in, bMitGrafik);

		in >> p_dVerbrauch >> p_dTankvolumen;
		// keine extra Werte laut Aufgabenstellung
		std::string startKreuzungName;
		double startZeitpunkt;

		in >> startKreuzungName;
		in >> startZeitpunkt;

		if (in.fail()) {
			throw std::runtime_error("PKW::vEinlesen: failed to read inputs");
		}

		if (p_dVerbrauch < 0.0) {
			throw std::runtime_error("PKW::vEinlesen: verbrauch < 0");
		}

		if (p_dTankvolumen < 0.0) {
			throw std::runtime_error("PKW::vEinlesen: tankvolumen < 0");
		}

		if (startKreuzungName.empty()) {
			throw std::runtime_error("PKW::vEinlesen: startKreuzungName empty");
		}
		if (startZeitpunkt < 0) {
			throw std::runtime_error("PKW::vEinlesen: startZeitpunkt < 0");
		}
	}
  // FIXME WIP CHECK

	virtual bool kannLosfahren() const override {
		return p_dTankinhalt > 0;
	}
};

#endif /* PKW_H_ */
