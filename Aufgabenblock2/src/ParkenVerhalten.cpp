/*
 * ParkenVerhalten.cpp
 *
 *  Created on: 27 Nov 2025
 *      Author: sulta
 */

#include "ParkenVerhalten.h"

ParkenVerhalten::ParkenVerhalten(Weg *weg, double startzeit): Verhalten(weg), p_dStartzeit(startzeit){

}

ParkenVerhalten::~ParkenVerhalten() {
}


double ParkenVerhalten::dStrecke(Fahrzeug& fzg, double dt) {
    if (dGlobaleZeit < p_dStartzeit) {
        return 0.0;
    }

    if (!p_bGestartet) {
        std::cout << fzg.getName() << " startet jetzt." << std::endl;
        p_bGestartet = true;
    }

    return 0.0;
}
