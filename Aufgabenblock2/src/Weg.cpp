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

Weg::Weg() :
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
	std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Name"
			<< std::setw(10) << "Laenge" << "Fahrzeuge" << std::endl;

	std::cout << std::setw(55) << std::setfill('-') << "-" << std::setfill(' ')
			<< std::endl;
}

void Weg::vAusgeben(std::ostream &os) const {
	SimulationsObjekt::vAusgeben(os);

	os << std::left << std::setw(10) << p_dLaenge << " (";

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
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
		try {
			(*it)->vSimulieren();
		} catch (Fahrausnahme &exception) {
			exception.vBearbeiten();
		}
	}

	// Aktualisieren
	p_pFahrzeuge.vAktualisieren();
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

const vertagt::VListe<std::unique_ptr<Fahrzeug>>& Weg::getFahrzeuge() const {
	return p_pFahrzeuge;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg) {
	fzg->vNeueStrecke(this);
	p_pFahrzeuge.push_back(std::move(fzg));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit) {
	fzg->vNeueStrecke(this, startzeit);
	p_pFahrzeuge.push_front(std::move(fzg));
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug &f) {
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
		Fahrzeug &fzg = **it; // Doppelte dereferenz, iterator->unique_ptr->Fahrzeug Objekt

		if (fzg == f) {
			std::unique_ptr<Fahrzeug> tempFzg = std::move(*it);

			p_pFahrzeuge.erase(it);

			return tempFzg;
		}
	}

	return nullptr;

}
