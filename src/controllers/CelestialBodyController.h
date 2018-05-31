/*
 * CelestialBodyController.h
 *
 *  Created on: 30 de mai de 2018
 *      Author: vitor
 */

#ifndef CELESTIALBODYCONTROLLER_H_
#define CELESTIALBODYCONTROLLER_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../models/Coordinate.h"
#include "../models/DefaultParams.h"
#include "../models/CelestialBody.h"
#include "../models/Params.h"

using namespace std;

class CelestialBodyController {
public:
	CelestialBodyController();
	virtual ~CelestialBodyController();

	void drawCelestialBodies(float angle);

	void initCelestialBodies(Params *params);
private:
	vector<CelestialBody *> *celestialBodies;
};

#endif /* CELESTIALBODYCONTROLLER_H_ */
