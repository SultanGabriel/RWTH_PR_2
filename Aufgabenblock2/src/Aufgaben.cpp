/*
 * Aufgaben.cpp
 *
 *  Created on: 23 Oct 2025
 *      Author: sulta
 */

#include "Aufgaben.h"

void vAufgabe1() {
	// Print a newline at the start of the exercise
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
				<< dGlobaleZeit << "h" << std::endl;

		vAusgabeTabelle(fahrzeuge);

		std::cout << std::endl; // extra newline nach der aufgabe

		// Hard break if dDelta is set to 0, then run only one simulation
		if (dDelta == 0) {
			return;

		}
	}
}

//Schreiben Sie eine neue Funktion vAufgabe 2(): Lesen Sie die Anzahl der zu erzeu-
//genden PKWs und Fahrr¨ader aus der Konsole ein, konstruieren Sie entsprechende
//Objekte der Klassen PKW und Fahrrad und verwalten Sie sie in einem
//vector<unique ptr<Fahrzeug>>. Warum k¨onnen/sollten Sie keine Fahrzeugob-
//jekte speichern? Warum k¨onnen Sie PKWs und Fahrr¨ader in einem gemeinsamen
//Vektor speichern?
//F¨uhren Sie f¨ur diese Objekte mehrere Simulationsschritte durch. Nach genau 3
//Stunden tanken Sie die PKWs nochmals voll. Die Zeitabfrage dazu soll im Testpro-
//gramm erfolgen, nicht innerhalb von dTanken(). Testen Sie dies mit verschiedenen
//Zeittakten. Geben Sie die Ergebnisse (Daten aller Fahrzeuge) nach jedem Schritt
//aus.
//Beachte: Gleichheit von double-Werten kann immer nur gegen eine Toleranz ϵ
//getestet werden, da Fließkomma-Berechnungen nicht komplett genau sind. Berech-
//nen Sie dazu z.B. den Absolutbetrag der Differenz bei Gleichheit oder reduzieren
//Sie eine der Seiten des Vergleichs um ϵ bei ≥ oder ≤. Die Funktion f¨ur den Ab-
//solutbetrag std::fabs() finden Sie in der Bibliothek <cmath>. Beachten Sie dieses
//Rundungsproblem bei allen weiteren Vergleichen zwischen Fließkomma-Werten.
void vAufgabe2() {
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

	int iAnzahlPKW = inputInt("Anzahl PKW: ");
	int iAnzahlFahrrad = inputInt("Anzahl Fahrrad: ");

	bool bAutoGen = bInputConfirmation(
			"Sollen die Fahrzeuge automatisch generiert werden?");

	// PKWs
	for (int i = 0; i < iAnzahlPKW; ++i) {
		if (bAutoGen) {
			std::string name = zufaelligerFahrzeugName();
			double vmax = 100 + std::rand() % 101;    // 100–200 km/h
			double verbrauch = 5 + std::rand() % 6;   // 5–10 L/100 km
			fahrzeuge.push_back(
					std::make_unique<PKW>(name, vmax, verbrauch, 40));
		} else {
			fahrzeuge.push_back(pkwInput());
		}
	}

	// Fahrräder
	for (int i = 0; i < iAnzahlFahrrad; ++i) {
		if (bAutoGen) {
			std::string name = "Fahrrad #" + std::to_string(i);
			double vmax = 20 + std::rand() % 11; // 20–30 km/h

			fahrzeuge.push_back(std::make_unique<Fahrrad>(name, vmax));
		} else {
			fahrzeuge.push_back(fahrradInput());
		}
	}

	double dEnd = inputDouble("Endzeit [h]: ");
	double dStep = inputDouble("Zeitschritt [h]: ");
	while (dGlobaleZeit < dEnd) {
		dGlobaleZeit += dStep;

		for (auto &f : fahrzeuge)
			f->vSimulieren();

		std::cout << std::endl << "Zeit: " << std::fixed << std::setprecision(2)
				<< dGlobaleZeit << " h" << std::endl;

		// Tankvorgang nach genau 3 h
		if (nearlyEqual(std::fmod(dGlobaleZeit, 3.0), 0.0)) {
			std::cout << "Tanke alle PKWs voll!" << std::endl;
			for (auto &f : fahrzeuge)
				f->dTanken();
		}

		vAusgabeTabelle(fahrzeuge);
	}

	std::cout << "=== Simulation beendet ===" << std::endl;
}

void vAufgabe3() {

	PKW pkw1("Audi", 180, 8);
	PKW pkw2("BMW", 200, 10);
	Fahrrad bike("Canyon", 28);

	std::cout << std::endl;
	Fahrzeug::vKopf();
	std::cout << pkw1 << std::endl << pkw2 << std::endl << bike << std::endl;
	// minimal simulieren, um Vergleich zu demonstrieren
	dGlobaleZeit = 1.0;
	pkw1.vSimulieren();
	dGlobaleZeit = 2.0;
	pkw2.vSimulieren();

	// Ausgabeoperator
	std::cout << std::endl;
	Fahrzeug::vKopf();
	std::cout << pkw1 << std::endl << pkw2 << std::endl << bike << std::endl;

	// Vergleich
	if (pkw1 < pkw2)
		std::cout << "pkw1 ist langsamer (weniger Strecke) als pkw2"
				<< std::endl;

	// Copy-Konstruktor verboten (prüfbar per Compiler-Fehler)
	// Fahrzeug f2 = f1; // ❌ sollte nicht kompilieren

	// Zuweisung
	PKW pkw3("VW", 160, 7);
	pkw3 = pkw1;
	std::cout << "Nach Zuweisung: " << pkw3 << std::endl;
	std::cout << "=== Simulation beendet ===" << std::endl;
}

// ---

using namespace std;
extern double dGlobaleZeit;
double dEpsilon = 0.001;

void vAufgabe_AB1() {

	int l = 0; // Laufindex für gezielte AUsgabe
	vector<int> ausgabe { 13 };
	double dTakt = 0.4;

	std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
	vecFahrzeuge.push_back(make_unique<PKW>("Audi", 217, 10.7));
	vecFahrzeuge.push_back(make_unique<Fahrrad>("BMX", 21.4));
	for (dGlobaleZeit = 0; dGlobaleZeit < 6; dGlobaleZeit += dTakt) {
		auto itL = find(ausgabe.begin(), ausgabe.end(), l);
		if (itL != ausgabe.end()) {
			std::cout << std::endl << l << " Globalezeit = " << dGlobaleZeit
					<< std::endl;
			Fahrzeug::vKopf();
		}

		for (int i = 0; i < vecFahrzeuge.size(); i++) {
			vecFahrzeuge[i]->vSimulieren();
			if (fabs(dGlobaleZeit - 3.0) < dTakt / 2) {
				vecFahrzeuge[i]->dTanken();
			}
			if (itL != ausgabe.end()) {
				std::cout << *vecFahrzeuge[i] << endl;
			}
		}
		l++;
	}
	char c;
	std::cin >> c;
}

// ---- Aufgabenblock 2 ----
void vAufgabe4() {
	std::cout << std::endl << "====        Aufgabe 4        ====" << std::endl;

	Weg::vKopf();

	Weg w1("Landstrasse_17", 12.5, Tempolimit::Landstrasse);

	std::cout << w1 << std::endl;
	std::cout << "=== Aufgabe 4 abgeschlossen ===" << std::endl;
}

void vAufgabe5() {
	std::cout << std::endl << "====        Aufgabe 5        ====" << std::endl;

	Weg w("Landstrasse_17", 12.5, Tempolimit::Landstrasse);
	// Fahrendes Fahrzeug
	auto f1 = std::make_unique<PKW>("BMW", 200, 8, 65);

	// Parkendes Fahrzeug, das ab Zeit 2.0 startet
	auto f2 = std::make_unique<PKW>("Audi", 180, 7, 55);

	w.vAnnahme(std::move(f1));           // fahrend
	w.vAnnahme(std::move(f2), 2.0);      // parken mit Startzeit

	std::cout << "Simulationsbegin..." << std::endl;

	const int maxI = 10;
	for (int i = 0; i < maxI; i++) {
		w.vSimulieren();

		std::cout << "\nZeit: " << dGlobaleZeit << " (" << i + 1 << "/" << maxI
				<< ")\n";

		Weg::vKopf();
		std::cout << w << std::endl;

		dGlobaleZeit += 0.5;
	}

	std::cout << "=== Aufgabe 5 abgeschlossen ===" << std::endl;
}

void vAufgabe6() {
	std::cout << std::endl << "====        Aufgabe 6        ====" << std::endl;

	dGlobaleZeit = 0.0;
	const int maxI = 50;

	// Grafik init
	bInitialisiereGrafik(800, 600);

	// Straßen
	std::string w1Name = "L17";
	std::string w2Name = "L71";
	Weg w1(w1Name, 500, Tempolimit::Landstrasse);
	Weg w2(w2Name, 500, Tempolimit::Landstrasse);

	int coords[4] = { 700, 250, 100, 200 };
	bZeichneStrasse(w1Name, w2Name, 500, 2, coords);

	// Fahrendes Fahrzeug
	auto fA1 = std::make_unique<PKW>("BMW", 200, 8, 65);
	auto fB1 = std::make_unique<PKW>("Mercedes", 180, 8, 65);

	// Parkendes Fahrzeug, das ab Zeit 2.0 startet
	auto fA2 = std::make_unique<PKW>("Audi", 190, 7, 55);
	auto fB2 = std::make_unique<PKW>("VW", 180, 7, 55);

	w1.vAnnahme(std::move(fA1));           // fahrend
	w1.vAnnahme(std::move(fA2), 2.75);      // parken mit Startzeit

	w2.vAnnahme(std::move(fB1));           // fahrend
	w2.vAnnahme(std::move(fB2), 3.75);      // parken mit Startzeit

	std::cout << std::endl << "Zeit: " << dGlobaleZeit << " (0/" << maxI << ")"
			<< std::endl;

	Weg::vKopf();
	std::cout << w1 << std::endl;
	std::cout << w2 << std::endl;

	std::cout << "Simulationsbegin..." << std::endl;
	for (int i = 0; i < maxI; i++) {
		dGlobaleZeit += 0.25;
		vSetzeZeit(dGlobaleZeit);

		std::cout << std::endl << "Zeit: " << dGlobaleZeit << " (" << i + 1
				<< "/" << maxI << ")" << std::endl;

		w1.vSimulieren();
		w2.vSimulieren();

		Weg::vKopf();
		std::cout << w1 << std::endl;
		std::cout << w2 << std::endl;
		// Update Fahrzeuge
		for (auto &fzg : w1.getFahrzeuge()) {
			fzg->vZeichnen(w1);
//			double rel = fzg->dAbschnittStrecke() / w1.dLaenge();
//			bZeichnePKW(fzg->getName(), w1.getName(), rel,
//					fzg->dGeschwindigkeit(),
//					dynamic_cast<PKW*>(fzg.get()) ?
//							dynamic_cast<PKW*>(fzg.get())->getTankinhalt() : 0);
		}

		for (auto &fzg : w2.getFahrzeuge()) {
			fzg->vZeichnen(w2);
//			double rel = fzg->dAbschnittStrecke() / w2.dLaenge();
//			bZeichnePKW(fzg->getName(), w2.getName(), rel,
//					fzg->dGeschwindigkeit(),
//					dynamic_cast<PKW*>(fzg.get()) ?
//							dynamic_cast<PKW*>(fzg.get())->getTankinhalt() : 0);
		}


		vSleep(100);
	}

	vBeendeGrafik();
	std::cout << "=== Aufgabe 6 abgeschlossen ===" << std::endl;
}


void vAufgabe6a() {
	std::cout << std::endl << "====        Aufgabe 6a       ====" << std::endl;

	// Random generator init
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1,10);

	// Variables
	const int N = 20;

	vertagt::VListe<int> liste;

	for (int i = 0;i < N; i++){
		liste.push_back(dist(device));
	}
	liste.vAktualisieren();

	std::cout << "--- Originale Liste ---" << std::endl;
	printVList(liste);

	std::cout << "--- Objekte > 5 loeschen ---" << std::endl;
	 for (auto it = liste.begin(); it != liste.end(); ++it)
	    {
	        if (*it > 5)
	        {
	            liste.erase(it);   // Diese Operation wird nur gespeichert!
	        }
	    }


	std::cout << "--- Liste nach erase, VOR vAktualisieren()  ---" << std::endl;
	printVList(liste);

	liste.vAktualisieren();
	std::cout << "--- Liste nach vAktualisieren()  ---" << std::endl;
	printVList(liste);

	std::cout << "--- 4 neue Elemente werden hinzugefuegt  ---" << std::endl;
	liste.push_back(98);
	liste.push_back(99);

	liste.push_front(1);
	liste.push_front(0);

	std::cout << "--- Liste nach hinzufuegen der Elemente, VOR vAktualisieren()  ---" << std::endl;
	printVList(liste);

	liste.vAktualisieren();
	std::cout << "--- Liste nach vAktualisieren()  ---" << std::endl;
	printVList(liste);

	std::cout << "=== Aufgabe 6a abgeschlossen ===" << std::endl;
}
