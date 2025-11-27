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
#include <iomanip>

#include "Logger.h"
#include "SimulationsObjekt.h"

// Globals
extern double dGlobaleZeit;

class Fahrzeug: public SimulationsObjekt {
protected:
	const double p_dMaxGeschwindigkeit;     // maximale Geschwindigkeit
	double p_dGesamtStrecke;
	double p_dGesamtZeit;

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

	// Methods
	static void vKopfDef(); // default kopf dings fixme look at this
	static void vKopf();

	virtual void vAusgeben(std::ostream &os) const override;

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
	Fahrzeug& operator=(const Fahrzeug &other);

};

#endif
