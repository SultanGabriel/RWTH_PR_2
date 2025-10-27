/*
 * Utils.h
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "Fahrzeug.h"
#include "Aufgaben.h"

#include <vector>
#include <memory>
#include <string>
#include <limits>


void vAufgaben();

void vAusgabeTabelle(const std::vector<std::unique_ptr<Fahrzeug>> &fahrzeuge);
void vAusgabeTabelle(const std::vector<std::shared_ptr<Fahrzeug>> &fahrzeuge);

double inputDouble(const std::string &prompt);
std::string inputString(const std::string &prompt);
int inputInt(const std::string &prompt);

#endif /* UTILS_H_ */
