/*
 * Simulation.cpp
 *
 *  Created on: Jan 25, 2026
 *      Author: sultan
 */

#include "Simulation.h"

#include "Kreuzung.h"

extern double dGlobaleZeit;
extern double FRAME_SLEEP;


Simulation::Simulation() {
	// TODO Auto-generated constructor stub

}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::vRegistriereKreuzung(const std::shared_ptr<Kreuzung> &k) {
	const std::string &name = k->getName();
	auto it = p_mapKreuzungen.find(name);
	if (it != p_mapKreuzungen.end()) {
		throw std::runtime_error("Kreuzung '" + name + "' existiert bereits!");
	}

	p_mapKreuzungen[name] = k;
	p_vecKreuzungen.push_back(k);
}
std::shared_ptr<Kreuzung> Simulation::pKreuzung(const std::string &name) const {
	auto it = p_mapKreuzungen.find(name);
	if (it == p_mapKreuzungen.end())
		throw std::runtime_error("Kreuzung '" + name + "' nicht gefunden!");

	return it->second;
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt) {
	for (double t = 0.0; t < dDauer; t += dZeitschritt) {
		dGlobaleZeit += dZeitschritt;

		if (p_bMitGrafik)
			vSetzeZeit(dGlobaleZeit);

		for (auto &k : p_vecKreuzungen)
			k->vSimulieren();

		if (p_bMitGrafik)
			vSleep(FRAME_SLEEP);
	}

	if (p_bMitGrafik)
		vBeendeGrafik();
}

#include <fstream>
#include <sstream>

void Simulation::vEinlesen(const std::string &dateiname, bool bMitGrafik) {
	p_bMitGrafik = bMitGrafik;

	std::ifstream infile(dateiname);
	if (!infile.is_open()) {
		throw std::runtime_error("vEinlesen: cannot open file: " + dateiname);
	}
// FIXME WIP CHECK
	std::string line;
	std::size_t lineNo = 0;

	// FIXME change error names to be more suitable??
	// FIXME fix all fixme's
	try {
		while (std::getline(infile, line)) {
			++lineNo;
			std::istringstream ss(line);

			std::string cmd;
			ss >> cmd;              // cmd IST jetzt ein normaler std::string
			if (cmd == "KREUZUNG") { /* ... */ }
			if (cmd.empty()) {
				throw std::runtime_error("Empty command");
			}
			if (cmd == "KREUZUNG") {

				// Create object, then read it from the line stream
//				Kreuzung k;
//				ss >> k; // calls SimulationsObjekt::operator>> -> virtual vEinlesen -> Kreuzung::vEinlesen
//				std::istringstream iss(line);

				auto pk = std::make_shared<Kreuzung>("", 0.0);   // dummy, wird gleich überschrieben durch vEinlesen
				ss >> *pk;                                      // trifft operator>>(istream&, SimulationsObjekt&)
//				vRegistriereKreuzung(pk); FIXMe this I'll need
				// TODO: store/register k somewhere (e.g., in a container or via a factory)
				// kreuzungen.push_back(k);  // if copyable
				// or better: kreuzungen.emplace_back(std::move(k));
				// or: auto pk = std::make_unique<Kreuzung>(); line >> *pk; list.push_back(std::move(pk));

			} else if (cmd == "STRASSE") {

				throw std::runtime_error("STRASSE: FIXME not implemented yet");

			} else if (cmd == "PKW") {

				throw std::runtime_error("PKW: FIXME not implemented yet");

			} else if (cmd == "FAHRRAD") {

				throw std::runtime_error("FAHRRAD: FIXME not implemented yet");

			} else {

				throw std::runtime_error(cmd + " does not exist!");

			}
		}

		if (!infile.eof() && infile.fail()) {
			throw std::runtime_error("I/O error while reading");
		}
	} catch (const std::exception &e) {
		// centralize all parsing errors here
		throw std::runtime_error(
				"vEinlesen: " + dateiname + ":" + std::to_string(lineNo) + " - "
						+ e.what());
	}
}

void Simulation::vGrafikAufbauen() {

}
