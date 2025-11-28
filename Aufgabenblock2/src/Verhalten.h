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

// Basis-klasse
class Verhalten {
protected:
    Weg* p_pWeg;

public:
    Verhalten(Weg* weg) : p_pWeg(weg) {}
    virtual ~Verhalten() = default;

    virtual double dStrecke(Fahrzeug& fzg, double dZeitIntervall) = 0;
    virtual Weg* getWeg() const;
};



#endif /* SRC_VERHALTEN_H_ */
