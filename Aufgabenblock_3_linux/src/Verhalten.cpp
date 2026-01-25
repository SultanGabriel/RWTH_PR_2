/*
 * Verhalten.cpp
 *
 *  Created on: 28 Nov 2025
 *      Author: sulta
 */

#include "Verhalten.h"
#include "Weg.h"


Verhalten::Verhalten(Weg *weg, VerhaltenTyp verhaltenTyp) :
			p_pWeg(weg), p_tVerhaltenTyp(verhaltenTyp) {
	}

Weg* Verhalten::getWeg() const {
	return p_pWeg;
}

// FIXME consider renaming to prefix with p ? what was the thing again??
VerhaltenTyp Verhalten::tVerhaltenTyp() {
	return p_tVerhaltenTyp;
}

