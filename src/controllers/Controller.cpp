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
const int PAUSE_BUTTON = 'p';
const int ENTER_BUTTON = 13;

const int CAMERA_0 = '0'; // camera inicial
const int CAMERA_1 = '1'; // camera do alto vendo todos os planetas
const int CAMERA_2 = '2'; // camera na diagonal
const int CAMERA_3 = '3'; // camera no satelite

const int SHOW_CAMERA_3 = 't'; // mostra a posicao da camera 3

bool showCamera3 = false;

float xCamera = 0;
float yCamera = 0;
float zCamera = 0;
float xCenter = 0;
float yCenter = 0;
float zCenter = 0;

float increment = 0.8;

int controller = 0;

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}


//PlanetController *Controller::planetController = new PlanetController();
CelestialBodyController *Controller::celestialBodyController = new CelestialBodyController();
ParamsController *Controller::paramsController = new ParamsController();

int Controller::SCREEN_PARAMS_ID = 1;
int Controller::SCREEN_PLANETS_ID = 2;

int Controller::screenId = Controller::SCREEN_PARAMS_ID;
int Controller::cameraId = -1;
int Controller::newCameraId = 0;

int Controller::TOP_CAMERA_ID = 1;
int Controller::DIAGONAL_CAMERA_ID = 2;
int Controller::SATELLITE_CAMERA_ID = 3;

float Controller::topCamera[] = {0, 90, -1, 0, 0, 0};
float Controller::diagonalCamera[] = {0, 20, -80, 0, 0, 0};
float Controller::satelliteCamera[] = {0, 0, 0, 0, 0, 0};
//
//static float topCamera[];
//static float diagonalCamera[];
//static float satelliteCamera[];


double angle = 0;


void Controller::specialKeyboardCallback(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[3] += increment;
				setCamera(cameraId);
			}

			break;
		case GLUT_KEY_RIGHT :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[3] -= increment;
				setCamera(cameraId);
			}

			break;
		case GLUT_KEY_UP :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[4] += increment;
				setCamera(cameraId);
			}

			break;
		case GLUT_KEY_DOWN :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[4] -= increment;
				setCamera(cameraId);
			}

			break;
		case GLUT_KEY_HOME :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[5] += increment;
				setCamera(cameraId);
			}

			break;
		case GLUT_KEY_END :
			if (cameraId == DIAGONAL_CAMERA_ID) {
				diagonalCamera[5] -= increment;
				setCamera(cameraId);
			}

			break;
	}

}

void Controller::keyboardCallback(unsigned char key, int x, int y) {
	int value = key;

	switch(key) {
	case PAUSE_BUTTON:
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
//		setCamera(0);
		newCameraId = 0;
		setCamera(newCameraId);

//		xCamera = 0, yCamera = 0, zCamera = 0;
//		xCenter = 0, yCenter = 0, zCenter = -90;

		break;
	case CAMERA_1:
//		setCamera(TOP_CAMERA_ID);
		newCameraId = TOP_CAMERA_ID;
		setCamera(newCameraId);
		break;
	case CAMERA_2:
//		setCamera(DIAGONAL_CAMERA_ID);
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
		controller = 1;
		break;
	case 'o':
		controller = 2;
		break;
	case 'w':
		if (controller == 1) {
			yCenter += increment;
		} else if (controller == 2) {
			yCamera += increment;
		}
		setCamera(newCameraId);
		break;
	case 'a':
		if (controller == 1) {
			xCenter -= increment;
		} else if (controller == 2) {
			xCamera -= increment;
		}
		setCamera(newCameraId);
		break;
	case 's':
		if (controller == 1) {
			yCenter -= increment;
		} else if (controller == 2) {
			yCamera -= increment;
		}
		setCamera(newCameraId);
		break;
	case 'd':
		if (controller == 1) {
			xCenter += increment;
		} else if (controller == 2) {
			xCamera += increment;
		}
		setCamera(newCameraId);
		break;
	case 'z':
		if (controller == 1) {
			zCenter -= increment;
		} else if (controller == 2){
			zCamera -= increment;
		}
		setCamera(newCameraId);
		break;
	case 'x':
		if (controller == 1) {
			zCenter += increment;
		} else if (controller == 2) {
			zCamera += increment;
		}
		setCamera(newCameraId);
		break;
	default:
		break;
	}

}

void Controller::drawScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	cout << "camera: (" << xCamera << ", " << yCamera << "," << zCamera << ") | centro: (" << xCenter << ", " << yCenter << ", " << zCenter << ")" << endl;
//
//	gluLookAt(xCamera, yCamera, zCamera,
//				xCenter, yCenter, zCenter,
//				0, 1, 0);

	if (Controller::screenId == Controller::SCREEN_PARAMS_ID) {

	} else if (Controller::screenId == Controller::SCREEN_PLANETS_ID) {
		if (showCamera3) {
			glPushMatrix();
				glTranslated(satelliteCamera[0], satelliteCamera[1], satelliteCamera[2]);
				glutWireCube(1);
			glPopMatrix();
		}

		celestialBodyController->drawCelestialBodies(angle);
	}

	glColor3f(1, 0.7, 0);

//	// Diz ao OpenGL para colocar o que desenhamos na tela
	glutSwapBuffers();
}

void Controller::update(int idx) {

	angle += 1;

//	if (cameraId == SATELLITE_CAMERA_ID) {
//		cout << "entrou na parada de atualizar a posicao" << endl;
		CameraCoordinate *cameraCoordinate = celestialBodyController->getCameraCoordinateBySatellitePosition(angle);

		if (cameraCoordinate != NULL) {
			satelliteCamera[0] = cameraCoordinate->getEyeCoordinate()->getX();
			satelliteCamera[1] = cameraCoordinate->getEyeCoordinate()->getY();
			satelliteCamera[2] = cameraCoordinate->getEyeCoordinate()->getZ();

			satelliteCamera[3] = cameraCoordinate->getCenterCoordinate()->getX();
			satelliteCamera[4] = cameraCoordinate->getCenterCoordinate()->getY();
			satelliteCamera[5] = cameraCoordinate->getCenterCoordinate()->getZ();

			setCamera(cameraId);
		} else {
			cout << "Sah porra é nula" << endl;
		}

//	}

	glutPostRedisplay();
	glutTimerFunc(DefaultParams::UPDATE_TIME, update, 0);
}

void Controller::setCamera(int newCameraId) {

	cameraId = newCameraId;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (cameraId == TOP_CAMERA_ID) {
		gluLookAt(topCamera[0], topCamera[1], topCamera[2],
				topCamera[3], topCamera[4], topCamera[5],
				0, 1, 0);
	} else if (cameraId == DIAGONAL_CAMERA_ID) {
		gluLookAt(diagonalCamera[0], diagonalCamera[1], diagonalCamera[2],
				diagonalCamera[3], diagonalCamera[4], diagonalCamera[5],
					0, 1, 0);
	} else if (cameraId == SATELLITE_CAMERA_ID) {
//		cout << "posicao da camera satelite: " << satelliteCamera[0] << ", " << satelliteCamera[1] << ", " << satelliteCamera[2] << ", " << satelliteCamera[3] << ", " << satelliteCamera[4] << ", " << satelliteCamera[5] << endl;
		gluLookAt(satelliteCamera[0], satelliteCamera[1], satelliteCamera[2],
				satelliteCamera[3], satelliteCamera[4], satelliteCamera[5],
					0, 1, 0);
	}

}
