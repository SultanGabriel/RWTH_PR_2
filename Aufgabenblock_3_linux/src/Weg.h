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

#include "lib/vertagt_liste.h"

#include "SimulationsObjekt.h"
#include "Tempolimit.h"

// forward declaration
class Fahrzeug;
enum class VerhaltenTyp
;
class Kreuzung;

class Weg: public SimulationsObjekt {
private:
	double p_dLaenge;
	double p_dVirtuelleSchranke;
	bool p_bUeberholVerbot;
	const std::weak_ptr<Kreuzung> p_pZielKreuzung;
	std::weak_ptr<Weg> p_pRueckweg;
protected:
	// std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	Tempolimit p_eTempolimit;

public:
	Weg();
//	Weg(std::string name, double laenge,
//			Tempolimit limit = Tempolimit::Autobahn);
	Weg(std::string name, double laenge,
			Tempolimit limit = Tempolimit::Autobahn,
			bool ueberholverbot = true,
	        std::shared_ptr<Kreuzung> ziel = nullptr);
	virtual ~Weg();

	static void vKopf();
	virtual void vAusgeben(std::ostream &os) const override;
	void vSimulieren() override;

	void vAnnahme(std::unique_ptr<Fahrzeug> fzg);
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit); // Annahme für Parkende fzg

	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug &f);

	// Getters
	double dTempolimit() const;
	double dLaenge() const;
	double dVirtuelleSchranke() const;
	bool bUeberholVerbot() const {
		return p_bUeberholVerbot;
	}
	const vertagt::VListe<std::unique_ptr<Fahrzeug>>& getFahrzeuge() const;
    // Getter gefordert: shared_ptr via lock()
    std::shared_ptr<Kreuzung> pZielKreuzung() const ;
    std::shared_ptr<Weg>      pRueckweg()     const ;

    // Setter für Rueckweg (nicht const möglich!)
    void vSetRueckweg(std::shared_ptr<Weg> rueck) { p_pRueckweg = rueck; }

	 void vEinlesen(std::istream& in, bool bMitGrafik) override {
	        SimulationsObjekt::vEinlesen(in, bMitGrafik);
//	        in >> p_dTankstelle;
//
//	        if(in.fail()){
//	            throw std::runtime_error("Kreuzung::vEinlesen: missing/invalid token");
//	        }
//	        if (p_dTankstelle < 0 ){
//	        	throw std::runtime_error("p_dTankstelle < 0");
    // FIXME WIP CHECK
//	        }
	    }
};

#endif /* SRC_WEG_H_ */

