/*
 * Params.cpp
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#include "Params.h"

Params::Params() {
	// TODO Auto-generated constructor stub

}

Params::~Params() {
	// TODO Auto-generated destructor stub
}

void Params::setPlanetsAmount(int planetsAmount) {
	this->planetsAmount = planetsAmount;
}

int Params::getPlanetsAmount() {
	return this->planetsAmount;
}

void Params::setArtificialSatelliteAmount(int artificialSatelliteAmount) {
	this->artificialSatelliteAmount = artificialSatelliteAmount;
}

int Params::getArtificialSatelliteAmount() {
	return this->artificialSatelliteAmount;
}

void Params::setNaturalSatelliteAmount(int naturalSatelliteAmount) {
	this->naturalSatelliteAmount = naturalSatelliteAmount;
}

int Params::getNaturalSatelliteAmount() {
	return this->naturalSatelliteAmount;
}
