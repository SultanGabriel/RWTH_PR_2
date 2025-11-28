/*
 * Weg.cpp
 *
 *  Created on: 26 Nov 2025
 *      Author: sulta
 */

#include <limits>

#include "Weg.h"
#include "Fahrzeug.h"
#include "ausnahmen/Fahrausnahme.h"

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

    bool first = true;
    for (const std::unique_ptr<Fahrzeug> &fzg : p_pFahrzeuge) {
    	if (!first) {
    		os << " ";
    	} else {
    		first = false;
    	}

        os << fzg->getName();
    }

    os << ")";
}

void Weg::vSimulieren() {
	for (auto &fzg : p_pFahrzeuge) {
		try {
		    fzg->vSimulieren();
		} catch (Fahrausnahme& e) {
			e.vBearbeiten();
		}

	}
}

double Weg::dTempolimit() const {
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

double Weg::dLaenge() const {
	return p_dLaenge;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg) {
    fzg->vNeueStrecke(this);
    p_pFahrzeuge.push_back(std::move(fzg));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit) {
    fzg->vNeueStrecke(this, startzeit);
    p_pFahrzeuge.push_front(std::move(fzg));
}
