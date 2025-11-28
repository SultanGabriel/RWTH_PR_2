/*
 * ParkenVerhalten.cpp
 *
 *  Created on: 27 Nov 2025
 *      Author: sulta
 */

#include "ParkenVerhalten.h"
#include "Utils.h"

ParkenVerhalten::ParkenVerhalten(Weg *weg, double startzeit): Verhalten(weg), p_dStartzeit(startzeit), p_bGestartet(false){

}

ParkenVerhalten::~ParkenVerhalten() {
}


double ParkenVerhalten::dStrecke(Fahrzeug& fzg, double dt) {
//    if (dGlobaleZeit < p_dStartzeit) {
//        return 0.0;
//    }

    if (!p_bGestartet && greaterOrEqual(dGlobaleZeit, p_dStartzeit)) {
        p_bGestartet = true;

        throw LosfahrenFahrausnahme(fzg, *p_pWeg);
    }

    return 0.0;
}
