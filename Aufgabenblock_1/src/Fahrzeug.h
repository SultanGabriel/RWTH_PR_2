/*
 * Fahrzeug.h
 *
 *  Created on: 22 Oct 2025
 *      Author: sulta
 */

#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <iostream>
#include <string>

class Fahrzeug {
private:
    std::string p_sName;
    const int p_iID;                 // eindeutige, konstante ID
    static int p_iMaxID;             // Klassenvariable für ID-Vergabe
    const double p_dMaxGeschwindigkeit;
    double p_dGesamtStrecke;
    double p_dGesamtZeit;

public:
    // Default-Konstruktor
    Fahrzeug()
        : p_sName(""), p_iID(++p_iMaxID), p_dMaxGeschwindigkeit(0),
		  p_dGesamtStrecke(0), p_dGesamtZeit(0){
        std::cout << "Fahrzeug (Default) erzeugt: Name=\""
                  << p_sName << "\", ID=" << p_iID << std::endl;
    }

    // Konstruktor mit Name
    Fahrzeug(const std::string& name)
        : p_sName(name),  p_iID(++p_iMaxID), p_dMaxGeschwindigkeit(0),
		  p_dGesamtStrecke(0), p_dGesamtZeit(0){
        std::cout << "Fahrzeug erzeugt: Name=\""
                  << p_sName << "\", ID=" << p_iID << std::endl;
    }
    // Konstruktor mit Name und maximale geschw.
    Fahrzeug(const std::string& name, const int maxGeschw)
        : p_sName(name),  p_iID(++p_iMaxID), p_dMaxGeschwindigkeit(maxGeschw),
		  p_dGesamtStrecke(0), p_dGesamtZeit(0){
        std::cout << "Fahrzeug erzeugt: Name=\""
                  << p_sName << "\", ID=" << p_iID << std::endl;
    }

    // Destruktor
    ~Fahrzeug() {
        std::cout << "Fahrzeug geloescht: Name=\""
                  << p_sName << "\", ID=" << p_iID << std::endl;
    }

    // Getter
    std::string getName() const { return p_sName; }
    int getID() const { return p_iID; }

    // Setter
    void setName(const std::string& name) { p_sName = name; }
};

#endif
