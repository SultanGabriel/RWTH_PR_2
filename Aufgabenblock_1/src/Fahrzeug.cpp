/*
 * Fahrzeug.cpp
 *
 *  Created on: 22 Oct 2025
 *      Author: sulta
 */

#include "Fahrzeug.h"

// Initialisierung der statischen Klassenvariable
int Fahrzeug::p_iMaxID = 0;

void Fahrzeug::vKopf() {
	std::cout << std::left << std::setw(5) << "ID" << std::setw(10) << "Name"
			<< std::setw(20) << "MaxGeschwindigkeit" << std::setw(15)
			<< "Gesamtstrecke" << std::endl << std::setfill('-')
			<< std::setw(50) << "-" << std::setfill(' ') << std::endl;
}

void Fahrzeug::vAusgeben() const {
	std::cout << std::left << std::setw(5) << p_iID << std::setw(10) << p_sName
			<< std::setw(20) << std::fixed << std::setprecision(2)
			<< p_dMaxGeschwindigkeit << std::setw(15) << std::fixed
			<< std::setprecision(2) << p_dGesamtStrecke;
}

void Fahrzeug::vSimulieren() {
    // Falls das Fahrzeug bereits in diesem Zeitschritt simuliert wurde
	// if (std::fabs(dGlobaleZeit - p_dZeit) < 1e-6) return;

    double dZeitDelta = dGlobaleZeit - p_dZeit;

    if (dZeitDelta > 0) {
        p_dGesamtZeit += dZeitDelta;
        p_dGesamtStrecke += p_dMaxGeschwindigkeit * dZeitDelta;
        p_dZeit = dGlobaleZeit;
    }
}
