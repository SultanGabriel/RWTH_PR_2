/*
 * ParkenVerhalten.cpp
 *
 *  Created on: 27 Nov 2025
 *      Author: sulta
 */

#include "ParkenVerhalten.h"
#include "Utils.h"

ParkenVerhalten::ParkenVerhalten(Weg *weg, double startzeit) :
				Verhalten(weg, VerhaltenTyp::PARKEN_VERHALTEN),
					p_dStartzeit(startzeit),
					p_bGestartet(false) {

}

ParkenVerhalten::~ParkenVerhalten() {
}

double ParkenVerhalten::dStrecke(Fahrzeug &fzg, double /*dt*/) {
    // vor Startzeit: stehen
    if (dGlobaleZeit < p_dStartzeit) {
        return 0.0;
    }

    // Startzeit erreicht: genau einmal Losfahren-Exception werfen
    if (!p_bGestartet && fzg.kannLosfahren()) {
        p_bGestartet = true;
        throw LosfahrenFahrausnahme(fzg, *getWeg());
    }

    // Solange Fahrzeug noch ParkenVerhalten hat: bleibt es stehen.
    // Nach dem Exception-Bearbeiten wird es auf FahrenVerhalten umgestellt.
    return 0.0;
}

//double ParkenVerhalten::dStrecke(Fahrzeug &fzg, double dt) {
//    if (dGlobaleZeit < p_dStartzeit) {
//        return 0.0;
//    }
//
//
//
//	if (fzg.kannLosfahren() && !p_bGestartet && greaterOrEqual(dGlobaleZeit, p_dStartzeit)) {
//		p_bGestartet = true;
//
//		throw LosfahrenFahrausnahme(fzg, *getWeg());
//	}
//
//	return 0.0;
//}
//
