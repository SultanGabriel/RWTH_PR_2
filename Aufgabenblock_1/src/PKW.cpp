/*
 * PKW.cpp
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */

#include "PKW.h"
#include <iomanip>
#include <iostream>

PKW::PKW(const std::string &name, double vmax, double verbrauch, double tankvol) :
				Fahrzeug(name, vmax),
					p_dVerbrauch(verbrauch),
					p_dTankvolumen(tankvol),
					p_dTankinhalt(tankvol / 2.0) {
}

double PKW::dTanken(double dMenge) {
	double diff = p_dTankvolumen - p_dTankinhalt;
	double nachgetankt = std::min(diff, dMenge);

	p_dTankinhalt += nachgetankt;

	std::cout << "Fahrzeug #" << p_iID << " " << p_sName << " wurde getankt ("
			<< nachgetankt << "L)" << std::endl;

	return nachgetankt;
}

void PKW::vSimulieren() {
	// wenn der tank leer ist, dann überspringen
	if (p_dTankinhalt <= 0.0)
		return;

	double oldTime = p_dZeit;

	Fahrzeug::vSimulieren();

	double deltaT = p_dZeit - oldTime;
	double gefahreneKm = p_dMaxGeschwindigkeit * deltaT;

	// Spritt Verbrauch
	double verbraucht = gefahreneKm * (p_dVerbrauch / 100.0);

	p_dTankinhalt -= verbraucht;
	if (p_dTankinhalt < 0.0)
		p_dTankinhalt = 0.0;
}

void PKW::vAusgeben(std::ostream &os) const {
	Fahrzeug::vAusgeben(os);
	os << std::setw(15) << std::fixed << std::setprecision(2) << p_dTankinhalt
			<< std::setw(10) << p_dVerbrauch;
}

void PKW::vKopf() {
	Fahrzeug::vKopf(); // print base part
	std::cout << std::setw(15) << "Tankinhalt" << std::setw(15) << "Verbrauch"
			<< std::endl << std::setfill('-') << std::setw(80) << "-"
			<< std::setfill(' ') << std::endl;
}
