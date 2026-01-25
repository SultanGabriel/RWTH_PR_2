/*
 * Fahrzeug.cpp
 *
 *  Created on: 22 Oct 2025
 *      Author: sulta
 */

#include "Utils.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "FahrenVerhalten.h"
#include "ParkenVerhalten.h"

// Konstruktoren
Fahrzeug::Fahrzeug() :
				SimulationsObjekt(""),
					p_dMaxGeschwindigkeit(0),
					p_dGesamtStrecke(0),
					p_dGesamtZeit(0),
					p_dAbschnittStrecke(0) {
}

Fahrzeug::Fahrzeug(const std::string &name) :
				SimulationsObjekt(name),
					p_dMaxGeschwindigkeit(0),
					p_dGesamtStrecke(0),
					p_dGesamtZeit(0),
					p_dAbschnittStrecke(0) {
}

Fahrzeug::Fahrzeug(const std::string &name, const double maxGeschw) :
				SimulationsObjekt(name),
					p_dMaxGeschwindigkeit(maxGeschw),
					p_dGesamtStrecke(0),
					p_dGesamtZeit(0),
					p_dAbschnittStrecke(0) {
}

Fahrzeug::~Fahrzeug() {
	// Leer
}

//
bool Fahrzeug::operator<(const Fahrzeug &rhs) const {
	return p_dGesamtStrecke < rhs.p_dGesamtStrecke;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug &other) {
	if (this != &other) {
		p_sName = other.p_sName;
		// p_iID NICHT kopieren
		// p_dMaxGeschwindigkeit auch NICHT (angenommen fix ab Konstruktion)
		// Strecken/Zeit zurücksetzen
		p_dGesamtStrecke = 0;
		p_dGesamtZeit = 0;
		p_dZeit = 0;
	}
	return *this;
}
//
//std::ostream& operator<<(std::ostream &os, const Fahrzeug &f) {
//	f.vAusgeben(os);   // polymorpher Aufruf
//	return os;
//}

//

void Fahrzeug::vKopfDef() {
	std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Name"
			<< std::setw(20) << "MaxGeschwindigkeit" << std::setw(15)
			<< "Gesamtstrecke" << std::endl << std::setfill('-')
			<< std::setw(50) << "-" << std::setfill(' ') << std::endl;
}

void Fahrzeug::vKopf() {
	std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Name"
			<< std::setw(20) << "MaxGeschwindigkeit" << std::setw(15)
			<< "Gesamtstrecke" << std::setw(15) << "Abschnittstrecke";
//	std::cout << std::left
//			  << std::setw(5)  << "ID"
//			  << std::setw(20) << "Name"
//			  << std::setw(20) << "MaxGeschw."
//			  << std::setw(15) << "Gesamtstrecke";
}

void Fahrzeug::vAusgeben(std::ostream &os) const {
	SimulationsObjekt::vAusgeben(os);

	os << std::left << std::setw(20) << std::fixed << std::setprecision(2)
			<< p_dMaxGeschwindigkeit << std::setw(15) << p_dGesamtStrecke
			<< std::setw(15) << p_dAbschnittStrecke;
}

void Fahrzeug::vSimulieren() {
	if (p_dZeit == dGlobaleZeit) {
		std::cout << "[WARN] Extensive vSimulieren call" << std::endl;
		return;
	}

	if (p_pVerhalten == nullptr) {
		std::cout << "[WARN] Shit p_pVerhalten == nullptr" << std::endl;
		return;
	}
//
//	double dt = dGlobaleZeit - p_dZeit;
//	p_dZeit = dGlobaleZeit;
//	p_dGesamtZeit += dt;
//
//	double strecke = p_pVerhalten->dStrecke(*this, dt);
//	p_dGesamtStrecke += strecke;
//	p_dAbschnittStrecke += strecke;

	const double dt = dGlobaleZeit - p_dZeit;

	const double s = p_pVerhalten->dStrecke(*this, dt); // kann werfen

	p_dZeit = dGlobaleZeit;
	p_dGesamtZeit += dt;
	p_dGesamtStrecke += s;
	p_dAbschnittStrecke += s;

}

double Fahrzeug::dTanken(double dMenge) {
	return 0.0; // Stub FIXME???
}

//void Fahrzeug::vNeueStrecke(Weg *weg) {
//	p_pVerhalten = std::make_unique<FahrenVerhalten>(weg);
//	p_dAbschnittStrecke = 0;
//
//}
//
//void Fahrzeug::vNeueStrecke(Weg *weg, double startzeit) {
//	p_pVerhalten = std::make_unique<ParkenVerhalten>(weg, startzeit);
//	p_dAbschnittStrecke = 0;
//}

void Fahrzeug::vNeueStrecke(Weg *weg) {
	if (!weg)
		throw std::runtime_error("Fahrzeug::vNeueStrecke: weg nullptr");

	p_pVerhalten = std::make_unique<FahrenVerhalten>(weg);
	p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vNeueStrecke(Weg *weg, double startzeit) {
	if (!weg)
		throw std::runtime_error(
				"Fahrzeug::vNeueStrecke(parkend): weg nullptr");

	p_pVerhalten = std::make_unique<ParkenVerhalten>(weg, startzeit);
	p_dAbschnittStrecke = 0.0;
}
VerhaltenTyp Fahrzeug::tVerhaltenTyp() {
	return p_pVerhalten->tVerhaltenTyp();
}
void Fahrzeug::vWechsleZuParken(Weg *weg, double startzeit) {
	p_pVerhalten = std::make_unique<ParkenVerhalten>(weg, startzeit);

	std::cout << "[WECHSEL] " << getName() << std::endl;
	// bewusst KEIN Reset von p_dAbschnittStrecke

}

