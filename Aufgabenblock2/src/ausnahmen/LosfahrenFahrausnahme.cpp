/*
 * LosfahrenFahrausnahme.cpp
 *
 *  Created on: 28 Nov 2025
 *      Author: sulta
 */

#include "LosfahrenFahrausnahme.h"
#include "../Fahrzeug.h"
#include "../Weg.h"

void LosfahrenFahrausnahme::vBearbeiten() {
	std::cout << "[AUSNAHME] [Losfahren] " << p_rFahrzeug.getName()
			<< " auf Weg " << p_rWeg.getName() << std::endl;

    p_rFahrzeug.vNeueStrecke(&p_rWeg);
}
