/*
 * SimulationsObjekt.cpp
 *
 *  Created on: 25 Nov 2025
 *      Author: sulta
 */

#include "SimulationsObjekt.h"

int SimulationsObjekt::p_iMaxID = 0;

SimulationsObjekt::SimulationsObjekt(std::string name) :
		p_sName(name), p_iID(++p_iMaxID), p_dZeit(0.0) {
}

SimulationsObjekt::~SimulationsObjekt() {
	std::cout << "Objekt geloescht: " << p_sName << ", ID=" << p_iID
			<< std::endl;
}

// Getters
std::string SimulationsObjekt::getName() const {
	return p_sName;
}

int SimulationsObjekt::getID() const {
	return p_iID;
}

// Setter
void SimulationsObjekt::setName(const std::string &name) {
	p_sName = name;
}

std::ostream& operator<<(std::ostream &os, const SimulationsObjekt &obj) {
	obj.vAusgeben(os);
	return os;
}

void SimulationsObjekt::vAusgeben(std::ostream &os) const {
	os << std::left << std::setw(5) << p_iID << std::setw(20) << p_sName;
}

void SimulationsObjekt::vKopf() {
	std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Name";
}
