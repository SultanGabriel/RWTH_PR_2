/*
 * FahrenVerhalten.h
 *
 *  Created on: 27 Nov 2025
 *      Author: sulta
 */

#ifndef SRC_FAHRENVERHALTEN_H_
#define SRC_FAHRENVERHALTEN_H_

#include "Verhalten.h"
#include "Fahrzeug.h"

class FahrenVerhalten: public Verhalten {
public:
	FahrenVerhalten(Weg *weg);

	virtual ~FahrenVerhalten();

	double dStrecke(Fahrzeug &fzg, double dt) override;
};

#endif /* SRC_FAHRENVERHALTEN_H_ */
