/*
 * Kreuzung.cpp
 *
 *  Created on: Jan 25, 2026
 *      Author: sultan
 */
#include "Tempolimit.h"

#include "Kreuzung.h"
#include "PKW.h"
#include "Weg.h"

#include <iostream>
#include <random>
#include <vector>

Kreuzung::Kreuzung() :
		SimulationsObjekt(""), p_dTankstelle(0) {
	// TODO Auto-generated constructor stub

}
Kreuzung::Kreuzung(std::string name, double tankstelle) :
		SimulationsObjekt(name), p_dTankstelle(tankstelle) {
	// TODO Auto-generated constructor stub

}

Kreuzung::~Kreuzung() {
	// TODO Auto-generated destructor stub
}

void Kreuzung::vVerbinde(
    const std::string& nameHin,
    const std::string& nameRueck,
    double laenge,
    std::shared_ptr<Kreuzung> start,
    std::shared_ptr<Kreuzung> ziel,
    Tempolimit limit,
    bool ueberholverbot)
{
    if (!start || !ziel) throw std::runtime_error("vVerbinde: start/zie l nullptr");

    auto hin  = std::make_shared<Weg>(nameHin,  laenge, limit, ueberholverbot, ziel);
    auto rueck= std::make_shared<Weg>(nameRueck,laenge, limit, ueberholverbot, start);

    hin->vSetRueckweg(rueck);
    rueck->vSetRueckweg(hin);

    start->p_pWege.push_back(hin);
    ziel->p_pWege.push_back(rueck);

    // FIXME (optional aber praktisch) Grafik: eine Straße zeichnen
    // bZeichneStrasse(start->getName(), ziel->getName(), laenge, 2, coords);
}
void Kreuzung::vTanken(Fahrzeug& fzg) {
    auto* pkw = dynamic_cast<PKW*>(&fzg);
    if (!pkw) return;

    double soll = pkw->dTankvolumen() - pkw->getTankinhalt();
    if (soll <= 0.0) return;

    if (p_dTankstelle > 0.0) {
        double menge = std::min(soll, p_dTankstelle);
        double getankt = pkw->dTanken(menge);
        p_dTankstelle -= getankt;
    } else {
        // Reserve: auch der letzte PKW wird voll
        pkw->dTanken(soll);
    }
}

void Kreuzung::vAusgeben(std::ostream &os) const {
	SimulationsObjekt::vAusgeben(os);
  // TODO Kreuzung::vAusgeben
}
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit)
{
    if (!fzg) throw std::runtime_error("Kreuzung::vAnnahme: fzg nullptr");
    if (p_pWege.empty()) throw std::runtime_error("Kreuzung::vAnnahme: keine abgehenden Wege bei " + getName());

    // ggf. tanken
    vTanken(*fzg);

    // erster abgehender Weg
    p_pWege.front()->vAnnahme(std::move(fzg), startzeit);
}
void Kreuzung::vSimulieren()
{
    // 1) erst alle Wege simulieren
    for (auto& weg : p_pWege) {
        weg->vSimulieren();
    }

    // 2) dann Status ausgeben (zeigt den Stand NACH dem Tick)
    std::cout << "Wege Kreuzung " << getName() << "\n";
    Weg::vKopf();
    for (auto& weg : p_pWege) {
        std::cout << *weg << "\n";
    }
}
std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& herkunft) {
    if (p_pWege.empty()) throw std::runtime_error("Kreuzung hat keine Wege: " + getName());

    if (p_pWege.size() == 1) return p_pWege.front();

    auto rueck = herkunft.pRueckweg();

    std::vector<std::shared_ptr<Weg>> cand;
    for (auto& w : p_pWege) {
        if (rueck && w == rueck) continue; // nicht zurück
        cand.push_back(w);
    }
    if (cand.empty()) return rueck ? rueck : p_pWege.front();

    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<size_t> dist(0, cand.size() - 1);
    return cand[dist(rng)];
}


//    void vKreuzung::Tanken(Fahrzeug& fzg);
//
//    void vKreuzung::Annahme(std::unique_ptr<Fahrzeug> fzg, double startzeit);
//
//    void vKreuzung::Simulieren() override;
//
//    std::shared_ptr<Weg> pKreuzung::ZufaelligerWeg(Weg& ankommenderWeg);
