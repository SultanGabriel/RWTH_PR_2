/*
 * LosfahrenFahrausnahme.h
 *
 *  Created on: 28 Nov 2025
 *      Author: sulta
 */

#ifndef SRC_AUSNAHMEN_LOSFAHRENFAHRAUSNAHME_H_
#define SRC_AUSNAHMEN_LOSFAHRENFAHRAUSNAHME_H_

#include "Fahrausnahme.h"

class LosfahrenFahrausnahme: public Fahrausnahme {
public:
	LosfahrenFahrausnahme(Fahrzeug &fzg, Weg &weg) :
			Fahrausnahme(fzg, weg) {
	}

	void vBearbeiten() override;
};

#endif /* SRC_AUSNAHMEN_LOSFAHRENFAHRAUSNAHME_H_ */
