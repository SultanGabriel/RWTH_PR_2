/*
 * Kreuzung.h
 *
 *  Created on: Jan 25, 2026
 *      Author: sultan
 */

#ifndef SRC_KREUZUNG_H_
#define SRC_KREUZUNG_H_

#include <list>
#include <memory>

#include "SimulationsObjekt.h"

class PKW;
class Weg;
class Fahrzeug;
enum class Tempolimit;   // falls bei dir existiert

class Kreuzung: public SimulationsObjekt {
private:
private:
	std::list<std::shared_ptr<Weg>> p_pWege;
	double p_dTankstelle;

public:
	Kreuzung(std::string name, double tankstelle = 0.0);
	~Kreuzung();

	static void vVerbinde(const std::string &nameHin,
			const std::string &nameRueck, double laenge,
			std::shared_ptr<Kreuzung> start, std::shared_ptr<Kreuzung> ziel,
			Tempolimit limit, bool ueberholverbot);

	void vTanken(Fahrzeug &fzg);

	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit);

	void vSimulieren() override;

	std::shared_ptr<Weg> pZufaelligerWeg(Weg &ankommenderWeg);
};

#endif /* SRC_KREUZUNG_H_ */
