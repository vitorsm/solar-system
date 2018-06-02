/*
 * ParamsController.cpp
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#include "ParamsController.h"

ParamsController::ParamsController() {

}

ParamsController::~ParamsController() {
	// TODO Auto-generated destructor stub
}


Params *ParamsController::getParams() {
	this->params = new Params();
	this->params->setPlanetsAmount(DefaultParams::DEFAULT_PLANETS_AMOUNT);
//	this->params->setPlanetsAmount(2);
	this->params->setArtificialSatelliteAmount(3);
	this->params->setNaturalSatelliteAmount(3);

	return this->params;
}
