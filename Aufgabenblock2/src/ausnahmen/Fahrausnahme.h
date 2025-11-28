/*
 * Fahrausnahme.h
 *
 *  Created on: 28 Nov 2025
 *      Author: sulta
 */

#ifndef SRC_AUSNAHMEN_FAHRAUSNAHME_H_
#define SRC_AUSNAHMEN_FAHRAUSNAHME_H_

#include <exception>
#include <string>

// forward declaration
class Fahrzeug;
class Weg;

class Fahrausnahme: public std::exception {
protected:
	Fahrzeug &p_rFahrzeug;
	Weg &p_rWeg;

public:
	Fahrausnahme(Fahrzeug &fzg, Weg &weg) :
			p_rFahrzeug(fzg), p_rWeg(weg) {
	}

	virtual void vBearbeiten() = 0;
};

#endif /* SRC_AUSNAHMEN_FAHRAUSNAHME_H_ */
