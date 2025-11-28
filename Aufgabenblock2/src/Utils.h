/*
 * Utils.h
 *
 *  Created on: 27 Oct 2025
 *      Author: sulta
 */

#ifndef UTILS_H_
#define UTILS_H_

// #include "Aufgaben.h"

#include <vector>
#include <memory>
#include <string>
#include <limits>
#include <cmath>

class PKW;
class Fahrrad;
class Fahrzeug;

void vAufgaben();

void vAusgabeTabelle(const std::vector<std::unique_ptr<Fahrzeug>> &fahrzeuge);
void vAusgabeTabelle(const std::vector<std::shared_ptr<Fahrzeug>> &fahrzeuge);

double inputDouble(const std::string &prompt);
std::string inputString(const std::string &prompt);
int inputInt(const std::string &prompt);
bool bInputConfirmation(const std::string &prompt);

std::string zufaelligerFahrzeugName();

std::unique_ptr<PKW> pkwInput();
std::unique_ptr<Fahrrad> fahrradInput();

// Toleranz für double-Vergleiche
constexpr double EPSILON = 1e-6;

// Vergleiche mit toleranz
bool nearlyEqual(double a, double b, double epsilon = EPSILON);
bool greaterOrEqual(double a, double b, double epsilon = EPSILON);
bool lessOrEqual(double a, double b, double epsilon = EPSILON);

#endif /* UTILS_H_ */
