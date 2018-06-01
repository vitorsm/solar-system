/*
 * CameraCoordinate.cpp
 *
 *  Created on: 1 de jun de 2018
 *      Author: vitor
 */

#include "CameraCoordinate.h"

CameraCoordinate::CameraCoordinate() {

	eyeCoordinate = new Coordinate(0, 0, 0);
	centerCoordinate = new Coordinate(0, 0, 0);
	upCoordinate = new Coordinate(0, 1, 0);

}
CameraCoordinate::~CameraCoordinate() {
	// TODO Auto-generated destructor stub
}

void CameraCoordinate::setEyeCoordinate(Coordinate *coordinate) {
	this->eyeCoordinate = coordinate;
}

Coordinate *CameraCoordinate::getEyeCoordinate() {
	return this->eyeCoordinate;
}


void CameraCoordinate::setCenterCoordinate(Coordinate *coordinate) {
	this->centerCoordinate = coordinate;
}

Coordinate *CameraCoordinate::getCenterCoordinate() {
	return this->centerCoordinate;
}
void CameraCoordinate::setUpCoordinate(Coordinate *coordinate) {
	this->upCoordinate = coordinate;
}
Coordinate *CameraCoordinate::getUpCoordinate() {
	return this->upCoordinate;
}
