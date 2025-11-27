/*
 * Utils.cpp
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */

#include "Utils.h"

// ------------------------------------------------------

void vAusgabeTabelle(const std::vector<std::unique_ptr<Fahrzeug>> &fahrzeuge) {
	Fahrzeug::vKopf();
	for (const auto &f : fahrzeuge) {
		std::cout << *f << std::endl;
	}
}

void vAusgabeTabelle(const std::vector<std::shared_ptr<Fahrzeug>> &fahrzeuge) {
	Fahrzeug::vKopf();
	for (const auto &f : fahrzeuge) {
		std::cout << *f << std::endl;
	}
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

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


bool bInputConfirmation(const std::string &prompt) {
    std::string input;

    while (true) {
        std::cout << prompt << " (j/n): ";
        std::getline(std::cin, input);

        if (input.empty()) continue;

        char c = std::tolower(input[0]);

        if (c == 'j' || c == 'y')
            return true;
        else if (c == 'n')
            return false;
        else
            std::cout << "Bitte 'j' oder 'n' eingeben." << std::endl;
    }
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

std::unique_ptr<PKW> pkwInput() {
	std:: cout << "PKW Erstellung" << std::endl;
	std::string sName = inputString("Name: ");
	double dVmax = inputDouble("Max. Geschwindigkeit [km/h]: ");
	double dVerbrauch = inputDouble("Verbrauch [L/100km]: ");

	return std::make_unique<PKW>(sName, dVmax, dVerbrauch);
}


std::unique_ptr<Fahrrad> fahrradInput() {
	std:: cout << "Fahrrad Erstellung" << std::endl;
	std::string sName = inputString("Name: ");
	double dVmax = inputDouble("Max. Geschwindigkeit [km/h]: ");

	return std::make_unique<Fahrrad>(sName, dVmax);
}

std::string zufaelligerFahrzeugName() {
    static std::vector<std::string> hersteller = {
        "BMW", "Audi", "Mercedes", "VW", "Opel", "Tesla",
        "Toyota", "Honda", "Ford", "Kawasaki", "Yamaha", "Ducati"
    };

    static std::vector<std::string> modelle = {
        "Speedster", "GT", "Racer", "Turbo", "Pro", "Classic", "Neo", "Plus", "Max"
    };



    // Seed only once
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    // random
    int i = std::rand() % hersteller.size();
    int j = std::rand() % modelle.size();

    return hersteller[i] + " " + modelle[j];
}


// Vergleiche
bool nearlyEqual(double a, double b, double epsilon) {
    return std::fabs(a - b) < epsilon;
}

bool greaterOrEqual(double a, double b, double epsilon) {
    return (a > b) || nearlyEqual(a, b, epsilon);
}

bool lessOrEqual(double a, double b, double epsilon) {
    return (a < b) || nearlyEqual(a, b, epsilon);
}
