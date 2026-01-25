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
#include "Utils.h"
#include "Verhalten.h"
#include "Kreuzung.h"

//enum class VerhaltenTyp;

Weg::Weg() :
				SimulationsObjekt::SimulationsObjekt(""),
					p_dLaenge(0),
					p_dVirtuelleSchranke(0),
					p_bUeberholVerbot(true),
					p_eTempolimit(Tempolimit::Autobahn) {
	// Leer
}

Weg::Weg(std::string name, double laenge, Tempolimit limit, bool ueberholverbot,
		std::shared_ptr<Kreuzung> ziel) :
				SimulationsObjekt::SimulationsObjekt(name),
					p_dLaenge(laenge),
					p_dVirtuelleSchranke(laenge),
					p_bUeberholVerbot(ueberholverbot),
					p_eTempolimit(limit),
					p_pZielKreuzung(ziel) {
	// Leer
//	 if (ziel)
//	    {
//	        p_pZielKreuzung = ziel; // weak_ptr bekommt shared_ptr zugewiesen
//	    }
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
  // FIXME  Weg::vAusgeben
}

void Weg::vSimulieren() {
    p_dVirtuelleSchranke = p_dLaenge;

	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
//	for (auto it = p_pFahrzeuge.end(); it != p_pFahrzeuge.begin(); ) {
//--it;
		try {

			auto &fzg = *it;
			fzg->vSimulieren();

//			double streckeGefahren = fzg->dAbschnittStrecke();

			//if (!p_bGestartet && greaterOrEqual(dGlobaleZeit, p_dStartzeit)) {
			if (p_bUeberholVerbot
					&& fzg->tVerhaltenTyp() == VerhaltenTyp::FAHREN_VERHALTEN) {
				p_dVirtuelleSchranke = fzg->dAbschnittStrecke() - 10; // FIXME make adjustable
				std::cout << "Uberholverbot fml " << fzg->getName() << " "
						<< " " << p_dVirtuelleSchranke
						<< std::endl;
			}

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
std::shared_ptr<Kreuzung> Weg::pZielKreuzung() const {
    return p_pZielKreuzung.lock();
}

std::shared_ptr<Weg> Weg::pRueckweg() const {
    return p_pRueckweg.lock();
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

double Weg::dVirtuelleSchranke() const {
	// Wenn Uberholverbot gilt, dann die virtuelle schranke, sonst
	return p_bUeberholVerbot ? p_dVirtuelleSchranke : p_dLaenge;
//	return p_dVirtuelleSchranke;
}
