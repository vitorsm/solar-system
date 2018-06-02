/*
 * Controller.cpp
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#include "Controller.h"

const int LEFT_BUTTON = 100;
const int RIGHT_BUTTON = 102;
const int ESC_BUTTON = 27;
const int SHOW_ROUTE_BUTTON = 'o';
const int ENTER_BUTTON = 13;
const int ON_OFF_LIGHT = 'l';

const int CAMERA_0 = '0'; // camera inicial
const int CAMERA_1 = '1'; // camera do alto vendo todos os planetas
const int CAMERA_2 = '2'; // camera na diagonal
const int CAMERA_3 = '3'; // camera no satelite

const int SHOW_CAMERA_3 = 't'; // mostra a posicao da camera 3

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}


CelestialBodyController *Controller::celestialBodyController = new CelestialBodyController();
ParamsController *Controller::paramsController = new ParamsController();

bool Controller::showRoute = false;
bool Controller::onLight = false;

float Controller::xCamera = 0;
float Controller::yCamera = 0;
float Controller::zCamera = 0;
float Controller::xCenter = 0;
float Controller::yCenter = 0;
float Controller::zCenter = 0;

int Controller::SCREEN_PARAMS_ID = 1;
int Controller::SCREEN_PLANETS_ID = 2;

int Controller::screenId = Controller::SCREEN_PARAMS_ID;
int Controller::cameraId = -1;
int Controller::newCameraId = 0;

int Controller::cameraController = 0;

int Controller::TOP_CAMERA_ID = 1;
int Controller::DIAGONAL_CAMERA_ID = 2;
int Controller::SATELLITE_CAMERA_ID = 3;

bool Controller::showCamera3 = false;
double Controller::camera3Distance = 1;

float Controller::topCamera[] = {0, 140, -1, 0, 0, 0};
float Controller::diagonalCamera[] = {0, 20, -80, 0, 0, 0};
float Controller::satelliteCamera[] = {0, 0, 0, 0, 0, 0};

double angle = 0;


void Controller::specialKeyboardCallback(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[3] += DefaultParams::CAMERA_INCREMENT;
				setCamera(cameraId);
			}

			break;
		case GLUT_KEY_RIGHT :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[3] -= DefaultParams::CAMERA_INCREMENT;
				setCamera(cameraId);
			}

			break;
		case GLUT_KEY_UP :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[4] += DefaultParams::CAMERA_INCREMENT;
				setCamera(cameraId);
			} else if (cameraId == SATELLITE_CAMERA_ID){
				camera3Distance -= DefaultParams::CAMERA_INCREMENT;
			}

			break;
		case GLUT_KEY_DOWN :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[4] -= DefaultParams::CAMERA_INCREMENT;
				setCamera(cameraId);
			} else if (cameraId == SATELLITE_CAMERA_ID){
				camera3Distance += DefaultParams::CAMERA_INCREMENT;
			}

			break;
		case GLUT_KEY_HOME :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[5] += DefaultParams::CAMERA_INCREMENT;
				setCamera(cameraId);
			}

			break;
		case GLUT_KEY_END :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[5] -= DefaultParams::CAMERA_INCREMENT;
				setCamera(cameraId);
			}

			break;
	}

}

void Controller::keyboardCallback(unsigned char key, int x, int y) {
	int value = key;

	switch(key) {
	case SHOW_ROUTE_BUTTON:
		showRoute = !showRoute;
		break;
	case ON_OFF_LIGHT:
		onLight = !onLight;
		break;
	case ENTER_BUTTON:
		cout << "enter button" << endl;
		if (screenId == SCREEN_PARAMS_ID) {
			screenId = SCREEN_PLANETS_ID;
			celestialBodyController->initCelestialBodies(paramsController->getParams());
		} else if (screenId == SCREEN_PLANETS_ID) {
		}
		break;
	case CAMERA_0:
		newCameraId = 0;
		setCamera(newCameraId);
		break;
	case CAMERA_1:
		newCameraId = TOP_CAMERA_ID;
		setCamera(newCameraId);
		break;
	case CAMERA_2:
		newCameraId = DIAGONAL_CAMERA_ID;
		setCamera(newCameraId);
		break;
	case CAMERA_3:
		newCameraId = SATELLITE_CAMERA_ID;
		setCamera(newCameraId);
		break;
	case ESC_BUTTON:
		break;
	case SHOW_CAMERA_3:
		showCamera3 = !showCamera3;
		break;
	case 'c':
		cameraController = 1;
		break;
	case 'i':
		cameraController = 2;
		break;
	case 'w':
		if (cameraController == 1) {
			yCenter += DefaultParams::CAMERA_INCREMENT;
		} else if (cameraController == 2) {
			yCamera += DefaultParams::CAMERA_INCREMENT;
		}
		setCamera(newCameraId);
		break;
	case 'a':
		if (cameraController == 1) {
			xCenter += DefaultParams::CAMERA_INCREMENT;
		} else if (cameraController == 2) {
			xCamera += DefaultParams::CAMERA_INCREMENT;
		}
		setCamera(newCameraId);
		break;
	case 's':
		if (cameraController == 1) {
			yCenter -= DefaultParams::CAMERA_INCREMENT;
		} else if (cameraController == 2) {
			yCamera -= DefaultParams::CAMERA_INCREMENT;
		}
		setCamera(newCameraId);
		break;
	case 'd':
		if (cameraController == 1) {
			xCenter -= DefaultParams::CAMERA_INCREMENT;
		} else if (cameraController == 2) {
			xCamera -= DefaultParams::CAMERA_INCREMENT;
		}
		setCamera(newCameraId);
		break;
	case 'z':
		if (cameraController == 1) {
			zCenter -= DefaultParams::CAMERA_INCREMENT;
		} else if (cameraController == 2){
			zCamera -= DefaultParams::CAMERA_INCREMENT;
		}
		setCamera(newCameraId);
		break;
	case 'x':
		if (cameraController == 1) {
			zCenter += DefaultParams::CAMERA_INCREMENT;
		} else if (cameraController == 2) {
			zCamera += DefaultParams::CAMERA_INCREMENT;
		}
		setCamera(newCameraId);
		break;
	default:
		break;
	}

}

void Controller::drawScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (Controller::screenId == Controller::SCREEN_PARAMS_ID) {

	} else if (Controller::screenId == Controller::SCREEN_PLANETS_ID) {
		if (showCamera3) {
			glPushMatrix();
				glTranslated(satelliteCamera[0], satelliteCamera[1], satelliteCamera[2]);
				glutWireCube(1);
			glPopMatrix();
		}

		celestialBodyController->drawCelestialBodies(angle, showRoute, onLight);
	}

	glutSwapBuffers();
}

void Controller::update(int idx) {

	angle += 1;

	CameraCoordinate *cameraCoordinate = celestialBodyController->getCameraCoordinateBySatellitePosition(angle, camera3Distance);

	if (cameraCoordinate != NULL) {
		satelliteCamera[0] = cameraCoordinate->getEyeCoordinate()->getX();
		satelliteCamera[1] = cameraCoordinate->getEyeCoordinate()->getY();
		satelliteCamera[2] = cameraCoordinate->getEyeCoordinate()->getZ();

		satelliteCamera[3] = cameraCoordinate->getCenterCoordinate()->getX();
		satelliteCamera[4] = cameraCoordinate->getCenterCoordinate()->getY();
		satelliteCamera[5] = cameraCoordinate->getCenterCoordinate()->getZ();

		setCamera(cameraId);
	}

	glutPostRedisplay();
	glutTimerFunc(DefaultParams::UPDATE_TIME, update, 0);
}

void Controller::setCamera(int newCameraId) {

	if (cameraId != newCameraId) {
		xCamera = 0, yCamera = 0, zCamera = 0;
		xCenter = 0, yCenter = 0, zCenter = 0;
	}
	cameraId = newCameraId;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (cameraId == TOP_CAMERA_ID) {
		gluLookAt(topCamera[0] + xCamera, topCamera[1] + yCamera, topCamera[2] + zCamera,
				topCamera[3] + xCenter, topCamera[4] + yCenter, topCamera[5] + zCenter,
				0, 1, 0);
	} else if (cameraId == DIAGONAL_CAMERA_ID) {
		gluLookAt(diagonalCamera[0] + xCamera, diagonalCamera[1] + yCamera, diagonalCamera[2] + zCamera,
				diagonalCamera[3] + xCenter, diagonalCamera[4] + yCenter, diagonalCamera[5] + zCenter,
					0, 1, 0);
	} else if (cameraId == SATELLITE_CAMERA_ID) {
		gluLookAt(satelliteCamera[0] + xCamera, satelliteCamera[1] + yCamera, satelliteCamera[2] + zCamera,
				satelliteCamera[3] + xCenter, satelliteCamera[4] + yCenter, satelliteCamera[5] + zCenter,
					0, 1, 0);
	}

}
