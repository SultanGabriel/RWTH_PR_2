/*
 * Aufgaben.h
 *
 *  Created on: 23 Oct 2025
 *      Author: sulta
 */

#ifndef AUFGABEN_H_
#define AUFGABEN_H_

#include <iostream>
#include <memory>       // für smart pointer
#include <vector>       // für std::vector

#include <iomanip>
#include <algorithm>
#include <random>

#include "Fahrzeug.h"
#include "Logger.h"
#include "Utils.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Utils.h"

#include "lib/SimuClient.h"
#include "lib/vertagt_liste.h"


static const int ANZAHL_AUFGABEN = 1;

void vAufgabe1();
void vRunSimulation1_8(); // unteraufgabe 8
void vAufgabe2();
void vAufgabe3();
void vAufgabe4();
void vAufgabe5();
void vAufgabe6();
void vAufgabe6a();

void vAufgabe_AB1();

void vAufgabe1a();

#endif /* AUFGABEN_H_ */
