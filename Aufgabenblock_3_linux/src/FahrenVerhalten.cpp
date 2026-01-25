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

double FahrenVerhalten::dStrecke(Fahrzeug &fzg, double dt) {
//	Weg* weg = getWeg();
//	double dGeschw = std::min(fzg.dGeschwindigkeit(), weg->dTempolimit());
//	double dEffStrecke = dGeschw * dt;
////	double dRestStrecke = getWeg()->dLaenge() - fzg.dAbschnittStrecke();
//	double dRestStrecke = getWeg()->dVirtuelleSchranke() - fzg.dAbschnittStrecke();
////	double dRestBisSchranke = getWeg()->dLaenge() - weg->dVirtuelleSchranke();
//	// if (p_pWeg->bUberholverbot)
//
//	//dRestStrecke = std::min(weg->dVirtuelleSchranke(), dRestStrecke);
////	double dSchranke = weg->dVirtuelleSchranke();
////	if (lessOrEqual(dSchranke,dRestStrecke)) {
////		std::cout << "FML\n";
////		return getWeg()->dLaenge()-dSchranke;
////	}
////	kkif(dRestBisSchranke, )){
////		return std::min(dRestBisSchranke, dEffStrecke);
////	}
//
//	if (lessOrEqual(dRestStrecke, 0)) {
//		throw StreckenendeFahrausnahme(fzg, *weg);
//	}
//
//
//
//	return std::min(dEffStrecke, dRestStrecke);
    Weg* weg = getWeg();

    double v = std::min(fzg.dGeschwindigkeit(), weg->dTempolimit());
    double dEff = v * dt;

    // Statt weg->dLaenge() jetzt weg->dSchranke()
    double dRest = weg->dVirtuelleSchranke() - fzg.dAbschnittStrecke();
	if (fzg.tVerhaltenTyp() == VerhaltenTyp::FAHREN_VERHALTEN){
		dRest = weg->dLaenge() - fzg.dAbschnittStrecke();

	}

    if (lessOrEqual(dRest, 0.0)) {
        throw StreckenendeFahrausnahme(fzg, *weg);
    }
    return std::min(dEff, dRest);
}
