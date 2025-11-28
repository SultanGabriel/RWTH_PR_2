/*
 * FahrenVerhalten.cpp
 *
 *  Created on: 27 Nov 2025
 *      Author: sulta
 */

#include "FahrenVerhalten.h"

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

	if (dRestStrecke <= 0) {
		std::cout << fzg.getName() << " ist am Ende des Weges angekommenn."
				<< std::endl;
		return 0.0;
	}

	return std::min(dEffStrecke, dRestStrecke);
}
