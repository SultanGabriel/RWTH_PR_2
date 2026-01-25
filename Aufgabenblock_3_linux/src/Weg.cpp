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
#include "PKW.h"

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
					p_pZielKreuzung(ziel),
					p_eTempolimit(limit) {
	// Leer
}

Weg::~Weg() {
	// Leer
}
void Weg::vKopf() {
	std::cout << std::left << std::setw(5) << "ID" << std::setw(14) << "Weg"
			<< std::setw(10) << "Laenge" << std::setw(10) << "Limit"
			<< std::setw(6) << "Uhv"        // Überholverbot
			<< std::setw(12) << "Schranke" << "Fahrzeuge" << "\n";

	std::cout << std::setw(90) << std::setfill('-') << "" << std::setfill(' ')
			<< "\n";
}

void Weg::vAusgeben(std::ostream &os) const {
	SimulationsObjekt::vAusgeben(os);

	os << std::left << std::setw(10) << p_dLaenge << std::setw(10)
			<< dTempolimit() << std::setw(6)
			<< (p_bUeberholVerbot ? "ja" : "nein") << std::setw(12)
			<< dVirtuelleSchranke() << "(";

	bool first = true;
	for (const auto &fzg : p_pFahrzeuge) {
		if (!fzg)
			continue;              // <<< WICHTIG

		if (!first)
			os << " ";
		first = false;

		// Name + Abschnitt + Typ
		os << fzg->getName() << ":" << std::fixed << std::setprecision(1)
				<< fzg->dAbschnittStrecke();

		// wenn PKW: Tank anzeigen
		if (auto *pkw = dynamic_cast<const PKW*>(fzg.get())) {
			os << "L" << std::setprecision(1) << pkw->getTankinhalt();
		}
	}
	os << ")";
}

void Weg::vSimulieren() {
	p_dVirtuelleSchranke = p_dLaenge;

//	Fahrzeug::vKopf();
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ) {
	    if (!(*it)) { ++it; continue; }

	    auto current = it;   // current merken
	    ++it;                // iterator IMMER vorziehen

	    try {
	        auto& fzg = *current;
	        fzg->vSimulieren();

	        if (p_bUeberholVerbot && fzg->tVerhaltenTyp() == VerhaltenTyp::FAHREN_VERHALTEN) {
	            p_dVirtuelleSchranke = fzg->dAbschnittStrecke();
	        }
	    } catch (Fahrausnahme& e) {
	        e.vBearbeiten();
	        // kein ++it hier mehr, ist schon passiert
	    }
	}

	// Aktualisieren
	p_pFahrzeuge.vAktualisieren();

	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
		if (!(*it))
			continue;                // <<< WICHTIG

		auto &fzg = *it;
		fzg->vZeichnen(*this);
	}
//FIXME DEBUG				std::cout << "\nWeg " << getName() << "\n";
//				for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
//				    auto& f = **it;
//				    std::cout << "  " << f.getName()
//				              << "  s=" << f.dAbschnittStrecke()
//				              << "  typ=" << static_cast<int>(f.tVerhaltenTyp())
//				              << "\n";
//				}
}

double Weg::dTempolimit() const {
	switch (p_eTempolimit) {
		case Tempolimit::Innerorts:
			return 50.0;

		case Tempolimit::Landstrasse:
			return 100.0;

		case Tempolimit::Autobahn:
		default:
			return std::numeric_limits<int>::infinity();
	}
}

double Weg::dLaenge() const {
	return p_dLaenge;
}

const vertagt::VListe<std::unique_ptr<Fahrzeug>>& Weg::getFahrzeuge() const {
	return p_pFahrzeuge;
}
std::shared_ptr<Kreuzung> Weg::pZielKreuzung() const {
	auto k = p_pZielKreuzung.lock();
	if (!k)
		throw std::runtime_error("Weg hat keine Zielkreuzung: " + getName());
	return k;
}

std::shared_ptr<Weg> Weg::pRueckweg() const {
	auto w = p_pRueckweg.lock();
	if (!w)
		throw std::runtime_error("Weg hat keinen Rueckweg: " + getName());
	return w;
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
		if (!(*it))
			continue;              // <<< WICHTIG: nullptr Einträge überspringen

		Fahrzeug &fzg = **it;
		if (fzg == f) {
			auto temp = std::move(*it);
			p_pFahrzeuge.erase(it);           // bei VListe evtl. "vertagt"
			return temp;
		}
	}

	// im Praktikum lieber knallen lassen => Fehler sofort sichtbar
	throw std::runtime_error(
			"Weg::pAbgabe: Fahrzeug '" + f.getName() + "' nicht auf Weg '"
					+ getName() + "' gefunden");
}

double Weg::dVirtuelleSchranke() const {
	// Wenn Uberholverbot gilt, dann die virtuelle schranke, sonst
	return p_bUeberholVerbot ? p_dVirtuelleSchranke : p_dLaenge;
}
