/*
 * Fahrrad.h
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include <cmath>
#include <iomanip>

#include "Fahrzeug.h"

class Fahrrad: public Fahrzeug {
public:
	Fahrrad(const std::string &name, double vmax) :
			Fahrzeug(name, vmax) {
	}
	virtual ~Fahrrad() override {
	}

	double dGeschwindigkeit() const override;
	void vSimulieren() override {
		Fahrzeug::vSimulieren();
	}
	void vAusgeben(std::ostream &os = std::cout) const override;
	static void vKopf();

	void vZeichnen(const Weg &weg) const override;

	void vEinlesen(std::istream &in, bool bMitGrafik) override {
		Fahrzeug::vEinlesen(in);
		// keine extra Werte laut Aufgabenstellung
		std::string startKreuzungName;
		double startZeitpunkt;

		in >> startKreuzungName;
		in >> startZeitpunkt;

		if (in.fail()) {
			throw std::runtime_error(
					"Fahrrad::vEinlesen: missing/invalid token");
		}

		if (startKreuzungName.empty()) {
			throw std::runtime_error(
					"Fahrrad::vEinlesen: startKreuzungName empty");
		}

		if (startZeitpunkt < 0) {
			throw std::runtime_error("Fahrrad::vEinlesen: startZeitpunkt < 0");
		}
// FIXME WIP CHECK
	}
};

#endif /* FAHRRAD_H_ */
