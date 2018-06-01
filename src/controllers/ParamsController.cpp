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
//	this->params->setPlanetsAmount(DefaultParams::DEFAULT_PLANETS_AMOUNT);
	this->params->setPlanetsAmount(1);
	this->params->setArtificialSatelliteAmount(1);
	this->params->setNaturalSatelliteAmount(1);

	return this->params;
}
