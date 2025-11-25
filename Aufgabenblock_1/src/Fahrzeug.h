/*
 * Fahrzeug.h
 *
 *  Created on: 22 Oct 2025
 *      Author: sulta
 */

#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <iostream>
#include <string>

#include "Logger.h"

// Globals
extern double dGlobaleZeit;

class Fahrzeug {
protected:
	static int p_iMaxID;                // Klassenvariable für ID-Vergabe

	std::string p_sName;
	const int p_iID;                        // eindeutige, konstante ID
	const double p_dMaxGeschwindigkeit;     // maximale Geschwindigkeit
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	double p_dZeit; 						// Zeitpunkt der letzten Simulation

public:
	// Konstruktor
	Fahrzeug();
	Fahrzeug(const std::string &name);
	Fahrzeug(const std::string &name, const double maxGeschw);

	// Damit schlägt jede Zeile fehl wie Fahrzeug f2 = f1; Das ist wichtig,
	// weil jede Fahrzeug-ID einzigartig sein soll und nicht kopiert werden darf
	Fahrzeug(const Fahrzeug&) = delete;

	// Virtueller Destruktor
	virtual ~Fahrzeug();

	// Getters und Setters
	std::string getName() const {
		return p_sName;
	}

	int getID() const {
		return p_iID;
	}

	// Setter
	void setName(const std::string &name) {
		p_sName = name;
	}

	// Methods
	static void vKopfDef(); // default kopf dings

	static void vKopf();

	virtual void vAusgeben(std::ostream &os = std::cout) const;
	virtual void vSimulieren();

	// Geschwindigkeit wird von Fahrrad überschrieben
	virtual double dGeschwindigkeit() const {
		return p_dMaxGeschwindigkeit;
	}

	// Tankfunktion
	virtual double dTanken(double dMenge =
			std::numeric_limits<double>::infinity());

	// Operator "<"
	bool operator<(const Fahrzeug &rhs) const;

	// Operator "="
	Fahrzeug& operator=(const Fahrzeug& other);


};

std::ostream& operator<<(std::ostream &os, const Fahrzeug &f);

#endif
