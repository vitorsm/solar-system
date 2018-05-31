/*
 * Coordinate.cpp
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#include "Coordinate.h"

Coordinate::Coordinate(float x, float y, float z) {

	this->x = x;
	this->y = y;
	this->z = z;

}

Coordinate::~Coordinate() {
	// TODO Auto-generated destructor stub
}


float Coordinate::getX() {
	return this->x;
}

float Coordinate::getY() {
	return this->y;
}

float Coordinate::getZ() {
	return this->z;
}
