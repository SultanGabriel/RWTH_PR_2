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
#include <memory>
#include <limits>

#include "lib/SimuClient.h"

#include "SimulationsObjekt.h"

class Verhalten;
class FahrenVerhalten;
class ParkenVerhalten;
class Weg;

// Globals
extern double dGlobaleZeit;

class Fahrzeug: public SimulationsObjekt {
protected:
	const double p_dMaxGeschwindigkeit;     // maximale Geschwindigkeit
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	std::unique_ptr<Verhalten> p_pVerhalten;
	double p_dAbschnittStrecke;

public:
	// ---       Konstruktor       ---
	Fahrzeug();
	Fahrzeug(const std::string &name);
	Fahrzeug(const std::string &name, const double maxGeschw);

	// Damit schlägt jede Zeile fehl wie Fahrzeug f2 = f1; Das ist wichtig,
	// weil jede Fahrzeug-ID einzigartig sein soll und nicht kopiert werden darf
	Fahrzeug(const Fahrzeug&) = delete;

	// Virtueller Destruktor
	virtual ~Fahrzeug();

	// ---         Methods         ---
	static void vKopfDef(); // default kopf dings fixme look at this
	static void vKopf();

	virtual void vAusgeben(std::ostream &os) const override;

	virtual void vSimulieren();
	virtual void vZeichnen(const Weg& weg) const { // To be overwritten...
		};

	// Geschwindigkeit wird von Fahrrad überschrieben
	virtual double dGeschwindigkeit() const {
		return p_dMaxGeschwindigkeit;
	}

	virtual double dAbschnittStrecke() const {
		return p_dAbschnittStrecke;
	}

	// Tankfunktion
	virtual double dTanken(double dMenge =
			std::numeric_limits<double>::infinity());

	void vNeueStrecke(Weg* weg);
	void vNeueStrecke(Weg* weg, double startzeit);

	// ---       Operatoren       ---
	// Operator "<"
	bool operator<(const Fahrzeug &rhs) const;

	// Operator "="
	Fahrzeug& operator=(const Fahrzeug &other);

};

#endif
