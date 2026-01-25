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
    // Hinweg: start -> ziel
    auto hin = std::make_shared<Weg>(nameHin, laenge, limit, ueberholverbot, ziel);

    // Rückweg: ziel -> start
    auto rueck = std::make_shared<Weg>(nameRueck, laenge, limit, ueberholverbot, start);

    // gegenseitig als Rückweg bekannt machen
    hin->vSetRueckweg(rueck);
    rueck->vSetRueckweg(hin);

    // in die jeweiligen Kreuzungen eintragen: "von hier wegführende Wege"
    start->p_pWege.push_back(hin);
    ziel->p_pWege.push_back(rueck);
}
void Kreuzung::vTanken(Fahrzeug& fzg)
{
    // Nur PKW tanken
    PKW* pkw = dynamic_cast<PKW*>(&fzg);
    if (!pkw) return;

    if (p_dTankstelle <= 0.0) return;

    // benötigte Menge um voll zu werden
    const double soll = pkw->dTankvolumen() - pkw->getTankinhalt();
    if (soll <= 0.0) return;

    // "Reserve": wir tanken immer voll, auch wenn Tankstelle eigentlich knapp wird
    // => einfach p_dTankstelle reduzieren, auch wenn negativ
    const double getankt = pkw->dTanken(soll);
    p_dTankstelle -= getankt;
}

void Kreuzung::vAusgeben(std::ostream &os) const {
	SimulationsObjekt::vAusgeben(os);
  // TODO Kreuzung::vAusgeben
}
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit)
{
    if (!fzg) return;

    // ggf. tanken
    vTanken(*fzg);

    if (p_pWege.empty())
    {
        // keine Wege -> Fahrzeug kann nirgendwo hin
        // Für die Aufgabe: einfach "fallen lassen"
        return;
    }

    // erster abgehender Weg
    auto ersterWeg = p_pWege.front();

    // parkend auf den Weg: startzeit > aktuelle Zeit => parken
    ersterWeg->vAnnahme(std::move(fzg), startzeit);
}
void Kreuzung::vSimulieren()
{
    for (auto& weg : p_pWege)
    {
        weg->vSimulieren();
    }
}
std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& ankommenderWeg)
{
    // Rückweg des ankommenden Weges
    auto rueck = ankommenderWeg.pRueckweg(); // shared_ptr via lock()

    // Kandidaten: alle Wege außer rueck
    std::vector<std::shared_ptr<Weg>> kandidaten;
    for (auto& w : p_pWege)
    {
        if (!rueck || w != rueck)
            kandidaten.push_back(w);
    }

    // Sackgasse: keine Alternative -> Rückweg nehmen
    if (kandidaten.empty())
    {
        return rueck;
    }

    // Zufall
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<size_t> dist(0, kandidaten.size() - 1);
    return kandidaten[dist(rng)];
}

//    void vKreuzung::Tanken(Fahrzeug& fzg);
//
//    void vKreuzung::Annahme(std::unique_ptr<Fahrzeug> fzg, double startzeit);
//
//    void vKreuzung::Simulieren() override;
//
//    std::shared_ptr<Weg> pKreuzung::ZufaelligerWeg(Weg& ankommenderWeg);
