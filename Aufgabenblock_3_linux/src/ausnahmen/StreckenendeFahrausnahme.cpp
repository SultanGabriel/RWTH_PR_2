#include "StreckenendeFahrausnahme.h"
#include "../Weg.h"
#include "../Kreuzung.h"
#include "../Fahrzeug.h"
#include "../Simulation.h"   // falls du dGlobaleZeit dort hast, sonst Utils/Globals include
#include <iostream>
#include <stdexcept>

void StreckenendeFahrausnahme::vBearbeiten() {
    auto ziel = p_rWeg.pZielKreuzung();
    if (!ziel) throw std::runtime_error("Streckenende: Weg hat keine Zielkreuzung: " + p_rWeg.getName());

    auto fzgPtr = p_rWeg.pAbgabe(p_rFahrzeug);
    if (!fzgPtr) throw std::runtime_error("Streckenende: pAbgabe nullptr (Fzg nicht gefunden) auf " + p_rWeg.getName());

    ziel->vTanken(*fzgPtr);

    auto neuerWeg = ziel->pZufaelligerWeg(p_rWeg);
    if (!neuerWeg) throw std::runtime_error("Streckenende: neuerWeg nullptr an " + ziel->getName());

    std::cout << "ZEIT: " << dGlobaleZeit << "\n"
              << "KREUZUNGWECHSEL\n"
              << "FAHRZEUG: " << fzgPtr->getName() << " [" << dGlobaleZeit << "]\n"
              << "KREUZUNG: " << ziel->getName() << "\n"
              << "WEG: " << p_rWeg.getName() << " -> " << neuerWeg->getName() << "\n";

    neuerWeg->vAnnahme(std::move(fzgPtr));
}
