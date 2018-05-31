/*
 * Planet.h
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "CelestialBody.h"

class Planet: public CelestialBody {
public:
	Planet();
	virtual ~Planet();
};

#endif /* PLANET_H_ */
