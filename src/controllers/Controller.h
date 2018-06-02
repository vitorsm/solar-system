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
#include "../models/CameraCoordinate.h"

using namespace std;

class Controller {
public:
	Controller();
	virtual ~Controller();

	static void drawScene();
	static void update(int idx);
	static void keyboardCallback(unsigned char key, int x, int y);
	static void specialKeyboardCallback(int key, int x, int y);

	static int SCREEN_PARAMS_ID;
	static int SCREEN_PLANETS_ID;

	static int TOP_CAMERA_ID;
	static int DIAGONAL_CAMERA_ID;
	static int SATELLITE_CAMERA_ID;

	static float topCamera[];
	static float diagonalCamera[];
	static float satelliteCamera[];

private:

	static bool onLight;
	static bool showRoute;

	static float xCamera;
	static float yCamera;
	static float zCamera;
	static float xCenter;
	static float yCenter;
	static float zCenter;

	static int cameraController;
	static bool showCamera3;
	static double camera3Distance;
	static void setCamera(int newCameraId);
	static CelestialBodyController *celestialBodyController;
	static ParamsController *paramsController;

	static int screenId;
	static int cameraId;
	static int newCameraId;

};

#endif /* CONTROLLER_H_ */
