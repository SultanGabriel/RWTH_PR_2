/*
 * StreckenendeFahrausnahme.cpp
 *
 *  Created on: 28 Nov 2025
 *      Author: sulta
 */

#include "StreckenendeFahrausnahme.h"
#include "../Fahrzeug.h"
#include "../Weg.h"

void StreckenendeFahrausnahme::vBearbeiten() {
	std::cout << "[AUSNAHME] [Streckenende] " << p_rFahrzeug.getName()
			<< " auf Weg " << p_rWeg.getName() << std::endl;

	// Fzg entfehrnen
	p_rWeg.pAbgabe(p_rFahrzeug);
}
