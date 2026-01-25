/*
 * Verhalten.h
 *
 *  Created on: 27 Nov 2025
 *      Author: sulta
 */

#ifndef SRC_VERHALTEN_H_
#define SRC_VERHALTEN_H_

class Weg;
class Fahrzeug;

enum class VerhaltenTyp {
	INIT_VERHALTEN, PARKEN_VERHALTEN, FAHREN_VERHALTEN
};

// Basis-klasse
class Verhalten {
private:
	Weg *p_pWeg;
	VerhaltenTyp p_tVerhaltenTyp;

public:
	Verhalten(Weg *weg,
			VerhaltenTyp verhaltenTyp = VerhaltenTyp::INIT_VERHALTEN);
	virtual ~Verhalten() = default;

	virtual double dStrecke(Fahrzeug &fzg, double dZeitIntervall) = 0;

	Weg* getWeg() const; // FIXME consider renaming
	VerhaltenTyp tVerhaltenTyp() ;
};

#endif /* SRC_VERHALTEN_H_ */
