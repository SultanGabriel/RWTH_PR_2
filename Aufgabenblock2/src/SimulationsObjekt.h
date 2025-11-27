/*
 * SimulationsObjekt.h
 *
 *  Created on: 25 Nov 2025
 *      Author: sulta
 */

#ifndef SRC_SIMULATIONSOBJEKT_H_
#define SRC_SIMULATIONSOBJEKT_H_

#include <string>
#include <iostream>
#include <iomanip>

class SimulationsObjekt {
protected:
	std::string p_sName;
	const int p_iID;
	double p_dZeit;

	static int p_iMaxID; // letzte Simulationszeit

public:
	SimulationsObjekt(std::string name);
	virtual ~SimulationsObjekt();

	virtual void vSimulieren() = 0; // reine virtuelle Methode
	virtual void vAusgeben(std::ostream &os) const;
	static void vKopf();

	bool operator==(const SimulationsObjekt &other) const {
		return p_iID == other.p_iID;
	}
	// Getters
	std::string getName() const;
	int getID() const;

	// Setter
	void setName(const std::string &name);
};

std::ostream& operator<<(std::ostream &os, const SimulationsObjekt &obj);

#endif /* SRC_SIMULATIONSOBJEKT_H_ */
