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

double angle = 0;


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
	case ESC_BUTTON:
		break;
	default:
		break;
	}

}

void Controller::drawScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (Controller::screenId == Controller::SCREEN_PARAMS_ID) {

	} else if (Controller::screenId == Controller::SCREEN_PLANETS_ID) {
		celestialBodyController->drawCelestialBodies(angle);
	}

//	glColor3f(1, 0.7, 0);
//
//	glPushMatrix();
//		glTranslated(0,0,-5);
//		glRotated(60,1,0,0);
//		glutWireSphere(1,50,50);
//	glPopMatrix();
//
//	glColor3f(0, 0, 1);
//
//	glPushMatrix();
//		glRotated(angle, 0, 0, 1);
//		glTranslated(-2, 0,-5);
//		glRotated(60,1,0,0);
//		glRotated(-angle, 0, 1, 0);
//		glutWireSphere(1,50,50);
//	glPopMatrix();
//
//	// Diz ao OpenGL para colocar o que desenhamos na tela
	glutSwapBuffers();
}

void Controller::update(int idx) {

	angle += 0.8;
	glutPostRedisplay();
	glutTimerFunc(DefaultParams::UPDATE_TIME, update, 0);
}


