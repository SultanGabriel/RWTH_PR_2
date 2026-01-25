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
enum class Tempolimit;

class Kreuzung: public SimulationsObjekt {
private:
	std::list<std::shared_ptr<Weg>> p_pWege;
	double p_dTankstelle;

public:
	Kreuzung();
	Kreuzung(std::string name, double tankstelle = 0.0);
	~Kreuzung();

	static void vVerbinde(const std::string &nameHin,
			const std::string &nameRueck, double laenge,
			std::shared_ptr<Kreuzung> start, std::shared_ptr<Kreuzung> ziel,
			Tempolimit limit, bool ueberholverbot);

	void vTanken(Fahrzeug &fzg);

	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit = 0);

	void vSimulieren() override;
	void vAusgeben(std::ostream &os) const override;

	std::shared_ptr<Weg> pZufaelligerWeg(Weg &ankommenderWeg);

	void vEinlesen(std::istream &in, bool bMitGrafik) override {
		SimulationsObjekt::vEinlesen(in, bMitGrafik);
		in >> p_dTankstelle;

		if (in.fail()) {
			throw std::runtime_error(
					"Kreuzung::vEinlesen: missing/invalid token");
		}
		if (p_dTankstelle < 0) {
			throw std::runtime_error("p_dTankstelle < 0");
		}
	}
  // FIXME WIP CHECK
};

#endif /* SRC_KREUZUNG_H_ */
