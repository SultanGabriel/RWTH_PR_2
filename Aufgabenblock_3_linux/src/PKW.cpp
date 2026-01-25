/*
 * PKW.cpp
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */

#include <iomanip>
#include <iostream>
#include <algorithm>

#include "PKW.h"
#include "Utils.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Verhalten.h"

#include "ausnahmen/LiegenGebliebenFahrausnahme.h"

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
    const double oldAbschnitt = p_dAbschnittStrecke;

    Fahrzeug::vSimulieren();

    double deltaS = p_dAbschnittStrecke - oldAbschnitt;

    // <<< FIX: wenn Abschnitt zurückgesetzt wurde (Wegwechsel), dann
    // ist "deltaS" negativ, obwohl evtl. Strecke gefahren wurde.
    // In dem Fall nehmen wir einfach die neue Abschnittsstrecke als delta.
    if (deltaS < 0.0) {
        deltaS = p_dAbschnittStrecke;
    }

    if (deltaS > 0.0) {
        const double verbraucht = deltaS * (p_dVerbrauch / 100.0);
        p_dTankinhalt -= verbraucht;

        if (p_dTankinhalt <= 0.0) {
            p_dTankinhalt = 0.0;

            // <<< wichtig: NICHT p_pVerhalten->getWeg() benutzen, wenn Verhalten evtl. schon gewechselt hat
            // Besser: aktuellen Weg vom Verhalten nehmen, aber nur wenn vorhanden:
            Weg* weg = p_pVerhalten ? p_pVerhalten->getWeg() : nullptr;
            if (!weg) throw std::runtime_error("PKW::vSimulieren: kein Weg beim Liegenbleiben");

            vWechsleZuParken(weg, 0.0);
        }
    }
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
double PKW::getTankinhalt() const {
	return p_dTankinhalt;
}
double PKW::dTankvolumen() const {
	return p_dTankvolumen;
}

double PKW::dGeschwindigkeit() const {
    if (p_dTankinhalt <= 0)
        return 0;

    return p_dMaxGeschwindigkeit;
}

void PKW::vZeichnen(const Weg& weg) const {
    double rel = p_dAbschnittStrecke / weg.dLaenge();

    bZeichnePKW(
        this->getName(),
        weg.getName(),
        rel,
        this->dGeschwindigkeit(),
        this->getTankinhalt()
    );
}
