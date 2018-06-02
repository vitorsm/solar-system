/*
 * CelestialBody.cpp
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#include "CelestialBody.h"

CelestialBody::CelestialBody() {
	this->coefRotation = 1;
	this->coefTranslation = 1;
	this->multRouteX = 1;
	this->multRouteZ = 1;
	this->celestialBodies = NULL;
}

CelestialBody::~CelestialBody() {
	// TODO Auto-generated destructor stub
}

void CelestialBody::setScale(float scale) {
	this->scale = scale;
}

float CelestialBody::getScale() {
	return this->scale;
}

void CelestialBody::setCoefTranslation(float coefTranslation) {
	this->coefTranslation = coefTranslation;
}

float CelestialBody::getCoefTranslation() {
	return this->coefTranslation;
}

void CelestialBody::setCoefRotation(float coefRotation) {
	this->coefRotation = coefRotation;
}

float CelestialBody::getCoefRotation() {
	return this->coefRotation;
}

void CelestialBody::setCoordinate(Coordinate *coordinate) {
	this->coordinate = coordinate;
}

Coordinate *CelestialBody::getCoordindate() {
	return this->coordinate;
}

vector<CelestialBody*> *CelestialBody::getCelestialBodies() {
	return this->celestialBodies;
}

void CelestialBody::addCelestialBody(CelestialBody *celestialBody) {

	if (this->celestialBodies == NULL) {
		this->celestialBodies = new vector<CelestialBody*>();
	}

	if (celestialBody != NULL) {
		this->celestialBodies->push_back(celestialBody);
	}
}

void CelestialBody::setMultRouteX(double multRouteX) {
	this->multRouteX = multRouteX;
}

double CelestialBody::getMultRouteX() {
	return this->multRouteX;
}

void CelestialBody::setMultRouteZ(double multRouteZ) {
	this->multRouteZ = multRouteZ;
}

double CelestialBody::getMultRouteZ() {
	return this->multRouteZ;
}
