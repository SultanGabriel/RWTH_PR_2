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
		Verhalten(weg) {

}

FahrenVerhalten::~FahrenVerhalten() {
	// TODO Auto-generated destructor stub
}

double FahrenVerhalten::dStrecke(Fahrzeug &fzg, double dt) {
	double vEff = std::min(fzg.dGeschwindigkeit(), p_pWeg->dTempolimit());
	double dEffStrecke = vEff * dt;
	double dRestStrecke = p_pWeg->dLaenge() - fzg.dAbschnittStrecke();

	if (lessOrEqual(dRestStrecke, 0)) {
		throw StreckenendeFahrausnahme(fzg, *p_pWeg);
	}

	return std::min(dEffStrecke, dRestStrecke);
}
