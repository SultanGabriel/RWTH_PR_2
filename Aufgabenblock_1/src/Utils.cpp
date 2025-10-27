/*
 * Utils.cpp
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */

#include "Utils.h"

void vAufgaben() {
	vAufgabe1();
}

// ------------------------------------------------------

void vAusgabeTabelle(const std::vector<std::unique_ptr<Fahrzeug>> &fahrzeuge) {
	Fahrzeug::vKopf();
	for (const auto &f : fahrzeuge) {
		f->vAusgeben();
		std::cout << std::endl;
	}
}

void vAusgabeTabelle(const std::vector<std::shared_ptr<Fahrzeug>> &fahrzeuge) {
	Fahrzeug::vKopf();
	for (const auto &f : fahrzeuge) {
		f->vAusgeben();
		std::cout << std::endl;
	}
}

// ------------------------------------------------------

std::string inputString(const std::string &prompt) {
	std::string line;
	std::cout << prompt;
	std::getline(std::cin, line);
	return line;
}

double inputDouble(const std::string &prompt) {
    std::string line;
    double value;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);

        std::stringstream ss(line);
        if (ss >> value && ss.eof()) {
            return value;
        }

        std::cout << "Ungültige Eingabe. Bitte eine Zahl eingeben!\n";
    }
}

int inputInt(const std::string &prompt) {
	std::string line;
	int value;

	while (true) {
		std::cout << prompt;
		std::getline(std::cin, line);

		std::stringstream ss(line);
		if (ss >> value && ss.eof()) {
			return value; // gültige Zahl, und sonst nix in der Zeile
		}

		std::cout << "Ungültige Eingabe. Bitte eine ganze Zahl eingeben!\n";
	}
}
