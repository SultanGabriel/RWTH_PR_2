/*
 * Weg.cpp
 *
 *  Created on: 26 Nov 2025
 *      Author: sulta
 */

#include <limits>

#include "Weg.h"
#include "Fahrzeug.h"

Weg::Weg():
				SimulationsObjekt::SimulationsObjekt(""),
					p_dLaenge(0),
					p_eTempolimit(Tempolimit::Autobahn) {
	// Leer
}

Weg::Weg(std::string name, double laenge, Tempolimit limit) :
				SimulationsObjekt::SimulationsObjekt(name),
					p_dLaenge(laenge),
					p_eTempolimit(limit) {
	// Leer
}

Weg::~Weg() {
	// Leer
}
void Weg::vKopf() {
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(10) << "Laenge"
              << "Fahrzeuge"
              << std::endl;

    std::cout << std::setw(55) << std::setfill('-') << "-" << std::setfill(' ')
              << std::endl;
}

void Weg::vAusgeben(std::ostream& os) const {
    SimulationsObjekt::vAusgeben(os);

    os << std::left
       << std::setw(10) << p_dLaenge
       << " (";

    for (auto& fzg : p_pFahrzeuge) {
        os << fzg->getName() << " ";
    }

    os << ")";
}

void Weg::vSimulieren() {
	for (auto &fzg : p_pFahrzeuge) {
		fzg->vSimulieren();
	}
}

double Weg::getTempolimit() const {
	switch (p_eTempolimit) {
		case Tempolimit::Innerorts:
			return 50.0;

		case Tempolimit::Landstrasse:
			return 100.0;

		case Tempolimit::Autobahn:
		default:
			return std::numeric_limits<int>::max();
	}
}

double Weg::getLaenge() const {
	return p_dLaenge;
}
