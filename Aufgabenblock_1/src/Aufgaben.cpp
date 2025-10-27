/*
 * Aufgaben.cpp
 *
 *  Created on: 23 Oct 2025
 *      Author: sulta
 */

#include "Aufgaben.h"

#include "Fahrzeug.h"
#include "Logger.h"
#include "Utils.h"

void vAufgabe1() {
	// Print a newline at the start of the exercise
	std::cout;
	std::cout << std::endl << "====        Aufgabe 1        ====" << std::endl;
//	logExeciseTitle("Aufgabe 1");

// Statische Objekte
	Fahrzeug f1("BMW");
	Fahrzeug f2("Audi");

	// Dynamische Objekte
	Fahrzeug *pF3 = new Fahrzeug("Mercedes");
	Fahrzeug *pF4 = new Fahrzeug("VW");

	// Nutzung der Objekte
	std::cout << "Statisches Fahrzeug 1: " << f1.getName() << std::endl;
	std::cout << "Statisches Fahrzeug 2: " << f2.getName() << std::endl;

	std::cout << "Dynamisches Fahrzeug 1: " << pF3->getName() << std::endl;
	std::cout << "Dynamisches Fahrzeug 2: " << pF4->getName() << std::endl;

	// Speicher wieder freigeben
	delete pF3;
	delete pF4;

	// Smart Pointer (unique_ptr)
	auto uF1 = std::make_unique<Fahrzeug>("Tesla");
	auto uF2 = std::make_unique<Fahrzeug>("Volvo");
	auto uF3 = std::make_unique<Fahrzeug>("Dacia");

	// Smart Pointer (shared_ptr)
	auto sF1 = std::make_shared<Fahrzeug>("Porsche");
	auto sF2 = std::make_shared<Fahrzeug>("Ferrari");

	std::cout << "use_count vor Zuweisung: sF1=" << sF1.use_count() << ", sF2="
			<< sF2.use_count() << std::endl;

	std::shared_ptr<Fahrzeug> sF3 = sF1; // Referenz teilen

	std::cout << "use_count nach Zuweisung: sF1=" << sF1.use_count() << ", sF3="
			<< sF3.use_count() << std::endl;

	std::cout << "Versuch Besitzübertrag mit unique_ptr" << std::endl;

	// unique_ptr kann NICHT kopiert werden, nur per move übertragen
	// auto uF4 = uF1; // Fehler, da ein uniquie_ptr nicht "kopiert" werden kann
	auto uF4 = move(uF1);
	if (!uF1) {
		std::cout << "uF1 ist nach move leer, Besitz liegt bei uF3."
				<< std::endl;
	}

	std::cout << "Versuch vector<unique_ptr<Fahrzeug>>" << std::endl;
	/*
	 * In dem Vektor können die Fahrzeuge, die mt unique_ptr erstellt wurden
	 * gespeichert werden. Die Besitzübertragung muss per move() stattfinden
	 *
	 */
	std::vector<std::unique_ptr<Fahrzeug>> vecUnique;

	vecUnique.push_back(move(uF2)); // Besitzübertragung per move
	vecUnique.push_back(move(uF3)); // Besitzübertragung per move
	vecUnique.push_back(move(uF4)); // Besitzübertragung per move

	std::cout << "Vektor mit unique_ptr enthält Fahrzeuge." << std::endl;
	std::cout << "Anzahl Fahrzeuge: " << vecUnique.size() << std::endl;
	std::cout << "Der Verktor wird jetzt gelöscht..." << std::endl;

	vAusgabeTabelle(vecUnique);

	vecUnique.clear(); // löscht alle Objekte

	/*
	 * In dem Vektor können die Fahrzeuge, die mt shared_ptr erstellt wurden
	 * gespeichert werden. Die Besitzübertragung kann per move() stattfinden,
	 * funktioniert aber auch ohne, dabei wird aber der use_count des pointers
	 * inkrementiert.
	 */
	std::cout << "vector<shared_ptr<Fahrzeug>>" << std::endl;
	std::vector<std::shared_ptr<Fahrzeug>> vecShared;

	// Beide Varianten erlaubt: mit und ohne move
	vecShared.push_back(sF1);        // Kopiem use_count++
	vecShared.push_back(move(sF2)); // Besitzübertragung, move ist optional bei shared_ptr

	std::cout << "use_count sF1: " << sF1.use_count() << std::endl;
	std::cout << "use_count sF2 (nach move): " << sF2.use_count()
			<< " (sollte 0 sein)" << std::endl;
	vAusgabeTabelle(vecShared);

	vecShared.clear(); // shared_ptrs im Vector werden zerstört

	std::cout << "====     ENDE: Aufgabe 1     ====" << std::endl;
}

void vRunSimulation1_8() {

	std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;
	fahrzeuge.push_back(std::make_unique<Fahrzeug>("BMW", 50));
	fahrzeuge.push_back(std::make_unique<Fahrzeug>("Audi", 70));

	for (int i = 0; i < 5; ++i) {
		dGlobaleZeit += 0.5; // 0.5 Stunden Schritte
		for (auto &f : fahrzeuge) {
			f->vSimulieren();
		}

		std::cout << "Zeit: " << dGlobaleZeit << "h" << std::endl;

		vAusgabeTabelle(fahrzeuge);

		std::cout << std::endl << std::endl;
	}

}

void vAufgabe1a() {
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

	// Eingabe von 3 Fahrzeugen
	for (int i = 0; i < 3; ++i) {
		std::string name = inputString(
				"Name des Fahrzeugs #" + std::to_string(i + 1) + ": ");

		double vmax = inputInt("Maximale Geschwindigkeit [km/h]: ");
		fahrzeuge.push_back(std::make_unique<Fahrzeug>(name, vmax));
	}

	// Simulationseinstellungen
	double dEndzeit = inputDouble("Endzeit der Simulation [h]: ");
	double dDelta = inputDouble("Zeittakt [h]: ");

	// Simulationsschleife
	while (dGlobaleZeit < dEndzeit) {
		dGlobaleZeit += dDelta;

		// Jedes Fahrzeug simulieren
		for (auto &f : fahrzeuge) {
			f->vSimulieren();
		}

		std::cout << std::endl << "Zeit: " << std::fixed << std::setprecision(2)
				<< dGlobaleZeit << "h\n";

		vAusgabeTabelle(fahrzeuge);

		std::cout << std::endl; // extra newline nach der aufgabe

		// Hard break if dDelta is set to 0, then run only one simulation
		if (dDelta == 0) {
			return;

		}
	}
}
