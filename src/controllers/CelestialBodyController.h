/*
 * CelestialBodyController.h
 *
 *  Created on: 30 de mai de 2018
 *      Author: vitor
 */

#ifndef CELESTIALBODYCONTROLLER_H_
#define CELESTIALBODYCONTROLLER_H_


#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>


#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../models/Coordinate.h"
#include "../models/DefaultParams.h"
#include "../models/CelestialBody.h"
#include "../models/Params.h"
#include "../models/CameraCoordinate.h"

using namespace std;

class CelestialBodyController {
public:
	CelestialBodyController();
	virtual ~CelestialBodyController();

	void drawCelestialBodies(float angle);

	void initCelestialBodies(Params *params);

	CameraCoordinate *getCameraCoordinateBySatellitePosition(float angle);
private:
	Coordinate *calculePosition(double distance, double angle);
	void configureLights();
	void initTextures();
	void drawSphere(float radius, int stacks, int columns);
	vector<CelestialBody *> *celestialBodies;
	int texture;
};

#endif /* CELESTIALBODYCONTROLLER_H_ */
