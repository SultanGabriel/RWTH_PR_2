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


double dGlobaleZeit = 0.0;


int main() {
	std::cout << "====== The application is initializing ======" << std::endl;


	std::unique_ptr<Fahrzeug> pFzg = std::make_unique<Fahrzeug>("audi", 12);

//	vAufgabe1();
//	vAufgabe1a();
//	vRunSimulation1_8();
//	vAufgabe2();
//	vAufgabe3();


	vAufgabe_AB1();

	std::cout << "====== The application is shutting down ======" << std::endl;
	std::cout << "====== See you next time! ======" << std::endl;

	std::cout << "Written by: Gabriel Sultan." << std::endl;

	return 0;
}

