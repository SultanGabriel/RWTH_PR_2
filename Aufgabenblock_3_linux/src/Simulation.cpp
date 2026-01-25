/*
 * Simulation.cpp
 *
 *  Created on: Jan 25, 2026
 *      Author: sultan
 */

#include "Simulation.h"

#include "Kreuzung.h"

#include "globals.h"


Simulation::Simulation() {
	// TODO Auto-generated constructor stub

}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::vRegistriereKreuzung(const std::shared_ptr<Kreuzung> &k) {
   const std::string& name = k->getName();

    if (p_mapKreuzungen(name))
        throw std::runtime_error("Kreuzung '" + name + "' existiert bereits!");

    p_mapKreuzungen[name] = k;
    p_vecKreuzungen.push_back(k);
}
std::shared_ptr<Kreuzung> Simulation::pKreuzung(const std::string& name) const
{
    auto it = p_mapKreuzungen.find(name);
    if (it == p_mapKreuzungen.end())
        throw std::runtime_error("Kreuzung '" + name + "' nicht gefunden!");

    return it->second;
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
      for (double t = 0.0; t < dDauer; t += dZeitschritt)
    {
        dGlobaleZeit += dZeitschritt;

        if (p_bMitGrafik)
            vSetzeZeit(dGlobaleZeit);

        for (auto& k : p_vecKreuzungen)
            k->vSimulieren();

        if (p_bMitGrafik)
            vSleep(FRAME_SLEEP);
    }

    if (p_bMitGrafik)
        vBeendeGrafik();
}
