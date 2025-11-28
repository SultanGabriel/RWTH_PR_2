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

	void vZeichnen(const Weg& weg) const override;

};

#endif /* FAHRRAD_H_ */
