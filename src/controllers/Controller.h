/*
 * Controller.h
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "../models/DefaultParams.h"
#include "CelestialBodyController.h"
#include "ParamsController.h"

using namespace std;

class Controller {
public:
	Controller();
	virtual ~Controller();

	static void drawScene();
	static void update(int idx);
	static void keyboardCallback(unsigned char key, int x, int y);

	static int SCREEN_PARAMS_ID;
	static int SCREEN_PLANETS_ID;

private:

	static CelestialBodyController *celestialBodyController;
	static ParamsController *paramsController;

	static int screenId;

};

#endif /* CONTROLLER_H_ */
