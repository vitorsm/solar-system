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
#include "../Utils.h"

using namespace std;

class CelestialBodyController {
public:
	CelestialBodyController();
	virtual ~CelestialBodyController();

	void drawCelestialBodies(float angle, bool showRoute, bool onLight);

	void initCelestialBodies(Params *params);

	CameraCoordinate *getCameraCoordinateBySatellitePosition(float angle, double cameraDistance);
private:
	bool onLight;
	void drawRote(double distance, double multX, double multZ);
	Coordinate *calculePosition(double distance, double angle, double multX, double multZ);
	void configureLights();
	void initTextures();
	void drawSphere(float radius, int stacks, int columns);
	vector<CelestialBody *> *celestialBodies;
	int planetTextures[11];
	int satelliteTextures[3];
};

#endif /* CELESTIALBODYCONTROLLER_H_ */
