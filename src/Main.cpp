//============================================================================
// Name        : solar-system.cpp
// Author      : Vitor Moreira
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>


#include "controllers/Controller.h"

using namespace std;

int xScreen = 500;
int yScreen = 500;


void setGlOrtho() {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	float ratio = (float)xScreen/(float)yScreen;
//	gluPerspective(60.0, ratio, 1.0, 200.0);
////	glFrustum(-ratio, ratio, -1.0, 1.0, 2.0, 100.0);
////	glOrtho(0.0, (double) 100, 0.0, (double) 100, -1, 1);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

	float ratio = (float)xScreen/(float)yScreen;
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(45, ratio, 0.5, 500);
}

void setup() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	setGlOrtho();

	// Propriedades do material da esfera
	float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
	float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

	float s = 50.0;
	float matShine[] = { s };

	// Definindo as propriedades do material
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void reshape(int width, int height) {
	xScreen = width;
	yScreen = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setGlOrtho();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void glutInitScreen(int *argc, char **argv) {
	glutInit(argc, argv);

	glutInitContextVersion(1, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 640);
	glutInitWindowPosition(100, 40);

	glutCreateWindow("Lunar Lander");

	glutDisplayFunc(Controller::drawScene);
//	glutReshapeFunc(reshape);
	glutKeyboardFunc(Controller::keyboardCallback);
	glutSpecialFunc(Controller::specialKeyboardCallback);
//	glutSpecialFunc(Controller::keyboardNotAsciiCallback);


	glutTimerFunc(DefaultParams::UPDATE_TIME, Controller::update, 0);

	setup();

	glutMainLoop();
}

int main(int argc, char **argv) {

	glutInitScreen(&argc, argv);

	return 0;
}
