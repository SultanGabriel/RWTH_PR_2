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

	// Fahrzeug aus dem alten weg abgeben
	auto ptr = p_rWeg.pAbgabe(p_rFahrzeug);

	// Wenn fahrzeug gefunden wurde
	if (ptr) {
		ptr->vNeueStrecke(&p_rWeg);

		p_rWeg.vAnnahme(std::move(ptr));
	}

}
