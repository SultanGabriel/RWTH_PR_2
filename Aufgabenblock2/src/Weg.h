/*
 * Weg.h
 *
 *  Created on: 26 Nov 2025
 *      Author: sulta
 */

#ifndef SRC_WEG_H_
#define SRC_WEG_H_

#include <list>
#include <iostream>
#include <string>
#include <memory>

#include "SimulationsObjekt.h"
#include "Tempolimit.h"

// forward declaration
class Fahrzeug;

class Weg: public SimulationsObjekt {
protected:
	double p_dLaenge;
	std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	Tempolimit p_eTempolimit;

public:
	Weg();
	Weg(std::string name, double laenge,
			Tempolimit limit = Tempolimit::Autobahn);
	virtual ~Weg();

	static void vKopf();
	virtual void vAusgeben(std::ostream &os) const override;
	void vSimulieren() override;

	void vAnnahme(std::unique_ptr<Fahrzeug> fzg);
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit); // Annahme für Parkende fzg

	// Getters
	double dTempolimit() const;
	double dLaenge() const;
    const std::list<std::unique_ptr<Fahrzeug>>& getFahrzeuge() const;

};

#endif /* SRC_WEG_H_ */

