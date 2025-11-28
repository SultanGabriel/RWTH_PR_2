/*
 * ParkenVerhalten.h
 *
 *  Created on: 27 Nov 2025
 *      Author: sulta
 */

#ifndef SRC_PARKENVERHALTEN_H_
#define SRC_PARKENVERHALTEN_H_

#include "Verhalten.h"
#include "Fahrzeug.h"

class ParkenVerhalten: public Verhalten {
protected:
    double p_dStartzeit;
	bool p_bGestartet = false;
public:
	ParkenVerhalten(Weg *weg, double startzeit);
	virtual ~ParkenVerhalten();

	double dStrecke(Fahrzeug &fzg, double dt) override;
};

#endif /* SRC_PARKENVERHALTEN_H_ */
