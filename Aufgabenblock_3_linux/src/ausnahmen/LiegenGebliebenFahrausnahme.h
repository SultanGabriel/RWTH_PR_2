/*
 * LiegenGebliebenFahrausnahme.h
 *
 *  Created on: Jan 25, 2026
 *      Author: sultan
 */

#ifndef SRC_AUSNAHMEN_LIEGENGEBLIEBENFAHRAUSNAHME_H_
#define SRC_AUSNAHMEN_LIEGENGEBLIEBENFAHRAUSNAHME_H_

#include "Fahrausnahme.h"

class LiegenGebliebenFahrausnahme: public Fahrausnahme {
public:
    LiegenGebliebenFahrausnahme(Fahrzeug& fzg, Weg& weg)
        : Fahrausnahme(fzg, weg) {}

    void vBearbeiten() override;
};

#endif /* SRC_AUSNAHMEN_LIEGENGEBLIEBENFAHRAUSNAHME_H_ */
