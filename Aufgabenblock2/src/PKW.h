/*
 * PKW.h
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */

#ifndef PKW_H_
#define PKW_H_

#include <limits>
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

	double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
	void vSimulieren() override;
	static void vKopf();
	void vAusgeben(std::ostream &os = std::cout) const override;
	double dGeschwindigkeit() const override;
};

#endif /* PKW_H_ */
