/*
 * Fahrzeug.cpp
 *
 *  Created on: 22 Oct 2025
 *      Author: sulta
 */

#include "Fahrzeug.h"

// Initialisierung der statischen Klassenvariable
int Fahrzeug::p_iMaxID = 0;

// Konstruktoren
Fahrzeug::Fahrzeug() :
				p_sName(""),
					p_iID(++p_iMaxID),
					p_dMaxGeschwindigkeit(0),
					p_dGesamtStrecke(0),
					p_dGesamtZeit(0),
					p_dZeit(0) {
}

Fahrzeug::Fahrzeug(const std::string &name) :
				p_sName(name),
					p_iID(++p_iMaxID),
					p_dMaxGeschwindigkeit(0),
					p_dGesamtStrecke(0),
					p_dGesamtZeit(0),
					p_dZeit(0) {
}

Fahrzeug::Fahrzeug(const std::string &name, const double maxGeschw) :
				p_sName(name),
					p_iID(++p_iMaxID),
					p_dMaxGeschwindigkeit(maxGeschw),
					p_dGesamtStrecke(0),
					p_dGesamtZeit(0),
					p_dZeit(0) {
	std::cout << "Fahrzeug erzeugt: Name=\"" << p_sName << "\", ID=" << p_iID
			<< std::endl;
	if (maxGeschw <= 0.0) {
		std::cout << "Fahrzeug erzeugt: Name=\"" << p_sName << "\", ID="
				<< p_iID << std::endl;

	}

}

Fahrzeug::~Fahrzeug() {
	std::cout << "Fahrzeug geloescht: Name=\"" << p_sName << "\", ID=" << p_iID
			<< std::endl;
}

//

bool Fahrzeug::operator<(const Fahrzeug &rhs) const {
	return p_dGesamtStrecke < rhs.p_dGesamtStrecke;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {
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

std::ostream& operator<<(std::ostream &os, const Fahrzeug &f) {
	f.vAusgeben(os);   // polymorpher Aufruf
	return os;
}

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
			<< "Gesamtstrecke" << std::endl << std::setfill('-')
			<< std::setw(50) << "-" << std::setfill(' ') << std::endl;
//	std::cout << std::left
//			  << std::setw(5)  << "ID"
//			  << std::setw(20) << "Name"
//			  << std::setw(20) << "MaxGeschw."
//			  << std::setw(15) << "Gesamtstrecke";
}
void Fahrzeug::vAusgeben(std::ostream &os) const {
	os << std::left << std::setw(5) << p_iID << std::setw(20) << p_sName
			<< std::setw(20) << std::fixed << std::setprecision(2)
			<< p_dMaxGeschwindigkeit << std::setw(15) << std::fixed
			<< std::setprecision(2) << p_dGesamtStrecke;
}

void Fahrzeug::vSimulieren() {
	double dZeitDelta = dGlobaleZeit - p_dZeit;

	if (dZeitDelta > 0) {
		p_dGesamtZeit += dZeitDelta;
		p_dGesamtStrecke += p_dMaxGeschwindigkeit * dZeitDelta;
		p_dZeit = dGlobaleZeit;
	}
}

double Fahrzeug::dTanken(double dMenge) {
	return 0.0; // Stub
}
