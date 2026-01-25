/*
 * Simulation.h
 *
 *  Created on: Jan 25, 2026
 *      Author: sultan
 */

#ifndef SRC_SIMULATION_H_
#define SRC_SIMULATION_H_

#include "lib/SimuClient.h"

#include <memory>
#include <vector>
#include <map>
#include <string>

// Forward declarations
class Kreuzung;

class Simulation {
private:
    bool p_bMitGrafik = false;

	std::map<std::string, std::shared_ptr<Kreuzung>> p_mapKreuzungen;
  	std::vector<std::shared_ptr<Kreuzung>> p_vecKreuzungen; // wird für simulationsloop benutzt, da es allg. scheneller ist



public:
	Simulation();

	~Simulation();


	void set


	std::shared_ptr<Kreuzung> pKreuzung(const std::string &name) const;


	void vGrafikAufbauen();


	void vRegistriereKreuzung(const std::shared_ptr<Kreuzung> &k);

	void vSimulieren(double dDauer, double dZeitschritt);
};

#endif /* SRC_SIMULATION_H_ */
