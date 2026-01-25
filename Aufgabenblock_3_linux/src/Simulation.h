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
#include <fstream>
#include <string>
#include <stdexcept>

#include "Utils.h"

// Forward declarations
class Kreuzung;


//struct StrassenGrafik
//{
//    std::string hin;
//    std::string rueck;
//    int laenge;
//    int nPaare;
//    std::vector<int> coords; // [x1,y1,x2,y2,...]
//};
class Simulation {
private:
    bool p_bMitGrafik = false;

	std::map<std::string, std::shared_ptr<Kreuzung>> p_mapKreuzungen;
  	std::vector<std::shared_ptr<Kreuzung>> p_vecKreuzungen; // wird für simulationsloop benutzt, da es allg. scheneller ist



public:
	Simulation();

	~Simulation();


	std::shared_ptr<Kreuzung> pKreuzung(const std::string &name) const;


	void vEinlesen(const std::string& datei, bool bMitGrafik = false);
	void vGrafikAufbauen();


	void vRegistriereKreuzung(const std::shared_ptr<Kreuzung> &k);

	void vSimulieren(double dDauer, double dZeitschritt);
};

#endif /* SRC_SIMULATION_H_ */
