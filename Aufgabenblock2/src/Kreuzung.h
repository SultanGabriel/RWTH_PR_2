/*
 * Kreuzung.h
 *
 *  Created on: 28 Nov 2025
 *      Author: sulta
 */

#ifndef SRC_KREUZUNG_H_
#define SRC_KREUZUNG_H_

#include "SimulationsObjekt.h"
#include <list>

class Weg;

class Kreuzung: public SimulationsObjekt {
private:
	std::list<Weg*> p_pWege;
public:
	Kreuzung();
	virtual ~Kreuzung();

	void vVerbinde(Weg* weg);
	Weg* pZufaelligerWeg();
};

#endif /* SRC_KREUZUNG_H_ */
