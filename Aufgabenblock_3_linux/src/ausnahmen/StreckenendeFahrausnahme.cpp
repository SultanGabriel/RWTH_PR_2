#include "StreckenendeFahrausnahme.h"
#include "../Weg.h"
#include "../Kreuzung.h"
#include "../Fahrzeug.h"
#include "../Simulation.h"   // falls du dGlobaleZeit dort hast, sonst Utils/Globals include
#include <iostream>
#include <stdexcept>

void StreckenendeFahrausnahme::vBearbeiten() {
    std::cout << "[AUSNAHME] [Streckenende] "
              << p_rFahrzeug.getName()
              << " auf Weg " << p_rWeg.getName()
              << std::endl;

    // 1) Zielkreuzung holen
    auto ziel = p_rWeg.pZielKreuzung();   // lock() intern
    if (!ziel) {
        throw std::runtime_error("StreckenendeFahrausnahme::vBearbeiten: Zielkreuzung expired/null");
    }

    // 2) Fahrzeug vom aktuellen Weg abgeben (unique_ptr übernehmen)
    auto fzgPtr = p_rWeg.pAbgabe(p_rFahrzeug);
    if (!fzgPtr) {
        throw std::runtime_error("StreckenendeFahrausnahme::vBearbeiten: pAbgabe returned nullptr");
    }

    // 3) ggf. tanken an der Kreuzung
    ziel->vTanken(*fzgPtr);

    // 4) neuen Weg wählen (nicht direkt zurück, außer Sackgasse)
    auto neuerWeg = ziel->pZufaelligerWeg(p_rWeg);
    if (!neuerWeg) {
        throw std::runtime_error("StreckenendeFahrausnahme::vBearbeiten: pZufaelligerWeg returned nullptr");
    }

    // 5) Ausgabe Kreuzungswechsel (Aufgabenformat sinngemäß)
    std::cout << "ZEIT: " << dGlobaleZeit << "\n"
              << "KREUZUNGWECHSEL\n"
              << "FAHRZEUG: " << fzgPtr->getName() << " [" << dGlobaleZeit << "]\n"
              << "KREUZUNG: " << ziel->getName() << "\n"
              << "WEG: " << p_rWeg.getName() << " -> " << neuerWeg->getName()
              << "\n";

    // 6) auf neuen Weg setzen (fahrend!)
    neuerWeg->vAnnahme(std::move(fzgPtr));
}
