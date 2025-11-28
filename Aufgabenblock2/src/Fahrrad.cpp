/*
 * Fahrrad.cpp
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */




#include "Fahrrad.h"
#include "Weg.h"

double Fahrrad::dGeschwindigkeit() const {
    double factor = std::pow(0.9, (p_dGesamtStrecke / 20.0));
    double v = p_dMaxGeschwindigkeit * factor;
    return std::max(v, 12.0);
}

void Fahrrad::vAusgeben(std::ostream& os) const {
    Fahrzeug::vAusgeben(os);
    os << std::setw(15) << std::fixed << std::setprecision(2) << dGeschwindigkeit();
}


void Fahrrad::vKopf() {
    Fahrzeug::vKopf(); // print base part
    std::cout << std::setw(15) << "Geschwindigkeit"
              << std::endl
              << std::setfill('-') << std::setw(80) << "-" << std::setfill(' ')
              << std::endl;
}

void Fahrrad::vZeichnen(const Weg& weg) const {
    double rel = p_dAbschnittStrecke / weg.dLaenge();

    bZeichneFahrrad(
        this->getName(),
        weg.getName(),
        rel,
        this->dGeschwindigkeit()
    );
}
