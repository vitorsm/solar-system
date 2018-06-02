/*
 * CelestialBodyController.cpp
 *
 *  Created on: 30 de mai de 2018
 *      Author: vitor
 */

#include "CelestialBodyController.h"

float piRad = M_PI / 180.0;

CelestialBodyController::CelestialBodyController() {

	srand(time(NULL));

}

CelestialBodyController::~CelestialBodyController() {
	// TODO Auto-generated destructor stub
}

void CelestialBodyController::initTextures() {
	if (planetTextures[0] == NULL) {
		for (int i = 0; i < 11; i++) {
			if (i == 0) {
				planetTextures[i] = SOIL_load_OGL_texture(
					"src/resources/sun2.jpg",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				);
			} else {
				cout << Utils::concatChar(Utils::concatValue("src/resources/planet_", i), ".jpg") << endl;
				planetTextures[i] = SOIL_load_OGL_texture(
					Utils::concatChar(Utils::concatValue("src/resources/planet_", i), ".jpg"),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				);
			}
		}

		for (int i = 0; i < 3; i++) {
			cout << Utils::concatChar(Utils::concatValue("src/resources/satellite_", (i + 1)), ".jpg") << endl;
			satelliteTextures[i] = SOIL_load_OGL_texture(
					Utils::concatChar(Utils::concatValue("src/resources/satellite_", (i + 1)), ".jpg"),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
		}
	}
	if (planetTextures[0] == NULL)
		cout << "Algo de errado não está certo com a textura: " << endl << SOIL_last_result() << endl;
}

void CelestialBodyController::configureLights() {

//	float difuseLight = 1.0;
//	float specLight = 1.0;
//	float globalAmbientLight = 0;
//
//	float globAmb[] = { globalAmbientLight, globalAmbientLight, globalAmbientLight, 1.0 };
//	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
//	float lightDif0[] = { difuseLight, difuseLight, difuseLight, 1.0 };
//	float lightSpec0[] = { specLight, specLight, specLight, 1.0 };
//	float lightDifAndSpec1[] = { 0.0, 1.0, 0.0, 1.0 };
//
//	// Propriedades da fonte de luz LIGHT0
//	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif0);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);
////	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec1);
////	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec1);
//
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);// Luz ambiente global
//	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false);// Enable local viewpoint
//
//	glEnable(GL_LIGHT0);

	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};          // "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

}

void CelestialBodyController::drawSphere(float radius, int stacks, int columns) {
	GLUquadric* quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluQuadricTexture(quadObj, GL_TRUE);
	gluSphere(quadObj, radius, stacks, columns);
	gluDeleteQuadric(quadObj);
}

void CelestialBodyController::drawCelestialBodies(float angle, bool showRoute, bool onLight) {

	this->onLight = onLight;

	this->initTextures();
	if (onLight) {
		this->configureLights();
		glEnable(GL_LIGHT0);
	}

	float depth = 0;

	CelestialBody *celestialBody = celestialBodies->at(0);

	if (onLight)
		glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);

	float lightPos0[] = { 0, 0, 0 };

	glBindTexture(GL_TEXTURE_2D, planetTextures[0]);
	glPushMatrix();
		glTranslated(0,0, depth);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		glColor3f(1, 1, 1);
		drawSphere(celestialBody->getScale(), 50, 50);
	glPopMatrix();

	if (onLight)
		glEnable(GL_LIGHTING);


	float s = 50.0;
	float matShine[] = { s };

	// Propriedades do material da esfera
	float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
	float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

	// Definindo as propriedades do material
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1, 0, 0);

	for (int i = 1; i < celestialBodies->size(); i++) {
		celestialBody = celestialBodies->at(i);

		glPushMatrix();
			Coordinate *coordinate = calculePosition(celestialBody->getCoordindate()->getX(),
					angle * celestialBody->getCoefTranslation(), celestialBody->getMultRouteX(), celestialBody->getMultRouteZ());

			if (showRoute) {
				drawRote(celestialBody->getCoordindate()->getX(), celestialBody->getMultRouteX(), celestialBody->getMultRouteZ());
			}

			glBindTexture(GL_TEXTURE_2D, planetTextures[i]);

			glColor3f(1, 1, 1);
			glTranslated(coordinate->getX(), coordinate->getY(), coordinate->getZ());
			glPushMatrix();
				glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
				glRotatef(angle * celestialBody->getCoefRotation(), 0, 1, 0);
				drawSphere(celestialBody->getScale(), 50, 50);
//				glutSolidSphere(celestialBody->getScale(), 50, 50);
			glPopMatrix();


			for (int j = 0; j < celestialBody->getCelestialBodies()->size(); j++) {
				CelestialBody *satellite = celestialBody->getCelestialBodies()->at(j);

				int count = rand() % 15 + 5;

				coordinate = calculePosition(satellite->getCoordindate()->getX(),
						angle * satellite->getCoefTranslation(), satellite->getMultRouteX(), satellite->getMultRouteZ());

				if (showRoute) {
					drawRote(satellite->getCoordindate()->getX(), satellite->getMultRouteX(), satellite->getMultRouteZ());
				}

				glBindTexture(GL_TEXTURE_2D, satelliteTextures[j]);

				glColor3f(1.0, 1.0, 1.0);
				glPushMatrix();
					glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
					glTranslated(coordinate->getX(), coordinate->getY(), coordinate->getZ());
					glRotatef((angle + j * DefaultParams::SATELLITE_DELAY * angle) * satellite->getCoefRotation(), 0, 1, 0);
					drawSphere(satellite->getScale(), 50, 50);
				glPopMatrix();

			}

		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);
	if (onLight)
		glDisable(GL_LIGHTING);
}

void CelestialBodyController::initCelestialBodies(Params *params) {

	celestialBodies = new vector<CelestialBody *>();

	float maxPercSatellite = 0.4;
	float maxPlanetSize = 2;
	float sunSize = 3;

	Coordinate *sunCoordinate = new Coordinate(0, 0, 0);

	CelestialBody *sun = new CelestialBody();
	celestialBodies->push_back(sun);

	sun->setCoordinate(sunCoordinate);
	sun->setScale(sunSize);
	sun->setCoefRotation(0);
	sun->setCoefTranslation(0);


	float initialDistancePlanet = 8;
	float initialDistanceSatellite = 1;


	float distancePlanet = initialDistancePlanet * 1.8;

	for (int i = 0; i < params->getPlanetsAmount(); i++) {

		CelestialBody *planet = new CelestialBody();
		celestialBodies->push_back(planet);

		float planetScale = rand() % (int) (maxPlanetSize * 700) / 1000.0;
		planetScale += 0.3 * maxPlanetSize;
		planet->setScale(planetScale);

		float planetRotation = rand() % (int) 700 / 1000.0;
		planetRotation += 0.3;
		float planetTranslation = rand() % (int) 700 / 1000.0;
		planetTranslation += 0.3;

		float multRouteX = rand() % (int) 1000 / 1000.0;
		multRouteX += 1;
		float multRouteZ = rand() % (int) 1000 / 1000.0;
		multRouteZ += 1;

		planet->setCoefRotation(planetRotation);
		planet->setCoefTranslation(planetTranslation);
		planet->setMultRouteX(multRouteX);
		planet->setMultRouteZ(multRouteZ);

		Coordinate *coordinate = new Coordinate(distancePlanet + planetScale, 0, 0);
		planet->setCoordinate(coordinate);

		int artificialSatellite = rand() % params->getArtificialSatelliteAmount() + 1;

		for (int j = 0; j < params->getArtificialSatelliteAmount(); j++) {

			float satelliteDistance = rand() % ((int) initialDistanceSatellite * 1000) / 1000.0 + initialDistanceSatellite;
			float satelliteMult = rand() % (int) (maxPercSatellite * 1000);

			satelliteMult /= 1000;

			CelestialBody *satellite = new CelestialBody();
			satellite->setScale(planetScale * satelliteMult);

			Coordinate *c = new Coordinate(planetScale + satellite->getScale() + satelliteDistance, 0, 0);
			satellite->setCoordinate(c);

			float satelliteRotation = rand() % (int) 1700 / 1000.0;
			satelliteRotation += 1.3;
			float satelletiTranslation = rand() % (int) 1700 / 1000.0;
			satelletiTranslation += 1.3;

			satellite->setCoefRotation(satelliteRotation);
			satellite->setCoefTranslation(satelletiTranslation);

			planet->addCelestialBody(satellite);
		}

		float val = rand() % ((int) initialDistancePlanet * 1000) / 1000.0;
		distancePlanet += val * multRouteX + planetScale;
	}

}

CameraCoordinate *CelestialBodyController::getCameraCoordinateBySatellitePosition(float angle, double cameraDistance) {

	if (celestialBodies != NULL) {

		CelestialBody *planet = celestialBodies->at(1);
		CelestialBody *satellite = NULL;

		double planetPosition[3];
		double satellitePosition[3];

		double rouboNegativoSafadeza = -1;

		if (planet->getCelestialBodies() != NULL && planet->getCelestialBodies()->size() > 0) {
			satellite = planet->getCelestialBodies()->at(0);

			Coordinate *planetCoordinate = calculePosition(planet->getCoordindate()->getX(),
					angle * planet->getCoefTranslation(), planet->getMultRouteX(), planet->getMultRouteZ());
			planetPosition[0] = planetCoordinate->getX();
			planetPosition[1] = planetCoordinate->getY();
			planetPosition[2] = planetCoordinate->getZ();

			double valCos = rouboNegativoSafadeza * cos( piRad * angle * satellite->getCoefTranslation() );
			double valSin = rouboNegativoSafadeza * sin( piRad * angle * satellite->getCoefTranslation() );


			Coordinate *satelliteCoordinate = calculePosition(satellite->getCoordindate()->getX(),
					angle * satellite->getCoefTranslation(), satellite->getMultRouteX(), satellite->getMultRouteZ());
			satellitePosition[0] = satelliteCoordinate->getX() + cameraDistance * valSin * planet->getMultRouteX();
			satellitePosition[1] = satelliteCoordinate->getY();
			satellitePosition[2] = satelliteCoordinate->getZ() + cameraDistance * valCos * planet->getMultRouteZ();

			CameraCoordinate *cameraCoordinate = new CameraCoordinate();
			cameraCoordinate->setEyeCoordinate(
								new Coordinate(satellitePosition[0] + planetPosition[0], satellitePosition[1] + planetPosition[1], satellitePosition[2] + planetPosition[2]));
			cameraCoordinate->setCenterCoordinate(
					new Coordinate(planetPosition[0], planetPosition[1], planetPosition[2]));

			return cameraCoordinate;
		}

	}

	return NULL;
}

void CelestialBodyController::drawRote(double distance, double multX, double multZ) {

	if (onLight)
		glDisable(GL_LIGHTING);

	glColor3f(1, 1, 1);
	int increment = 1;
	Coordinate *c = NULL;

	for (int i = 0; i < 360; i += increment) {
		c = calculePosition(distance, i, multX, multZ);

		glPushMatrix();
			glTranslated(c->getX(), c->getY(), c->getZ());
			glutSolidCube(0.05);
		glPopMatrix();
	}

	if (onLight)
		glEnable(GL_LIGHTING);
}

Coordinate *CelestialBodyController::calculePosition(double distance, double angle, double multX, double multZ) {
	double position[3];

	double rouboNegativoSafadeza = -1;

	position[0] = rouboNegativoSafadeza * sin( piRad * angle ) *
			distance * multX;
	position[2] = rouboNegativoSafadeza * cos( piRad * angle ) *
			distance * multZ;

	return new Coordinate(position[0], position[1], position[2]);
}
