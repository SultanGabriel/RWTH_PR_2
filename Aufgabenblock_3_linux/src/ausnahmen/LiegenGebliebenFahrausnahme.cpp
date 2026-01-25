/*
 * LiegenGebliebenFahrausnahme.cpp
 *
 *  Created on: Jan 25, 2026
 *      Author: sultan
 */

#include "LiegenGebliebenFahrausnahme.h"
#include "../Fahrzeug.h"
#include "../Weg.h"

void LiegenGebliebenFahrausnahme::vBearbeiten() {
	std::cout << "[AUSNAHME] [Liegen Geblieben] Tank vom Fahrzeug " << p_rFahrzeug.getName()
			<< " auf dem Weg " << p_rWeg.getName() << " ist leer!" << std::endl;

	// Fzg entfehrnen
	p_rWeg.pAbgabe(p_rFahrzeug);
}
