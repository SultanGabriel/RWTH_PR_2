/*
 * StreckenendeAusnahme.h
 *
 *  Created on: 28 Nov 2025
 *      Author: sulta
 */

#ifndef SRC_AUSNAHMEN_STRECKENENDEFAHRAUSNAHME_H_
#define SRC_AUSNAHMEN_STRECKENENDEFAHRAUSNAHME_H_

#include "Fahrausnahme.h"

class StreckenendeFahrausnahme : public Fahrausnahme {
public:
    StreckenendeFahrausnahme(Fahrzeug& fzg, Weg& weg)
        : Fahrausnahme(fzg, weg) {}

    void vBearbeiten() override;
};


#endif /* SRC_AUSNAHMEN_STRECKENENDEFAHRAUSNAHME_H_ */
