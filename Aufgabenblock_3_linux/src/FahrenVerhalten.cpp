/*
 * FahrenVerhalten.cpp
 *
 *  Created on: 27 Nov 2025
 *      Author: sulta
 */

#include "FahrenVerhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Utils.h"

FahrenVerhalten::FahrenVerhalten(Weg *weg) :
		Verhalten(weg, VerhaltenTyp::FAHREN_VERHALTEN) {

}

FahrenVerhalten::~FahrenVerhalten() {
	// TODO Auto-generated destructor stub
}

//double FahrenVerhalten::dStrecke(Fahrzeug &fzg, double dt) {
//
//	Weg *weg = getWeg();
//
//	double v = std::min(fzg.dGeschwindigkeit(), weg->dTempolimit());
//	double dEff = v * dt;
//
//	// Statt weg->dLaenge() jetzt weg->dSchranke()
//	double dRest = weg->dVirtuelleSchranke() - fzg.dAbschnittStrecke();
//	if ((!weg->bUeberholVerbot())
//			&& fzg.tVerhaltenTyp() == VerhaltenTyp::FAHREN_VERHALTEN) {
//		dRest = weg->dLaenge() - fzg.dAbschnittStrecke();
//
//	}
//
//	if (lessOrEqual(dRest, 0.0)) {
//		throw StreckenendeFahrausnahme(fzg, *weg);
//	}
//	return std::min(dEff, dRest);
//}
double FahrenVerhalten::dStrecke(Fahrzeug &fzg, double dt) {
    Weg* weg = getWeg();

    double v = std::min(fzg.dGeschwindigkeit(), weg->dTempolimit());
    double dEff = v * dt;

    const double dRestEnde = weg->dLaenge() - fzg.dAbschnittStrecke();
    if (lessOrEqual(dRestEnde, 0.0)) {
        throw StreckenendeFahrausnahme(fzg, *weg);
    }

    const double dRestSchranke = weg->dVirtuelleSchranke() - fzg.dAbschnittStrecke();
    const double dZulaessig = std::min(dRestEnde, std::max(0.0, dRestSchranke));

    return std::min(dEff, dZulaessig);
}

