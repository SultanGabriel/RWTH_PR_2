//============================================================================
// Name        : Main.cpp
// Author      : G. Sultan
// Version     : Alpha 0.1
// Copyright   : Unlicense
//============================================================================

#include <string>
#include <iostream>

#include "Fahrzeug.h"
#include "Aufgaben.h"
#include "Utils.h"

void vRunSimulation_8();

double dGlobaleZeit = 0.0;


int main() {
	int iTestIndex = 1;

	std::cout << "====== The application is initializing ======" << std::endl;



//	vRunSimulation_8();
	vAufgabe1a();



	std::cout << "====== The application is shutting down ======" << std::endl;
	std::cout << "====== See you next time! ======" << std::endl;

	std::cout << "Written by: Gabriel Sultan." << std::endl;

	return 0;
}

