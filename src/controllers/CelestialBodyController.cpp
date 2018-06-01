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
	if (texture == NULL) {
		texture = SOIL_load_OGL_texture(
				"src/resources/mars-small.jpg",
//				"src/resources/vitor.jpg",
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	}
	if (texture == NULL)
		cout << "Algo de errado não está certo com a textura: " << endl << SOIL_last_result() << endl;
}

void CelestialBodyController::configureLights() {

	float difuseLight = 1.0;
	float specLight = 1.0;
	float globalAmbientLight = 0.2;

	float globAmb[] = { globalAmbientLight, globalAmbientLight, globalAmbientLight, 1.0 };
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDif0[] = { difuseLight, difuseLight, difuseLight, 1.0 };
	float lightSpec0[] = { specLight, specLight, specLight, 1.0 };

	// Propriedades da fonte de luz LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);        // Luz ambiente global
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false);// Enable local viewpoint

	glEnable(GL_LIGHT0);

}

void CelestialBodyController::drawSphere(float radius, int stacks, int columns) {
	GLUquadric* quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluQuadricTexture(quadObj, GL_TRUE);
	gluSphere(quadObj, radius, stacks, columns);
	gluDeleteQuadric(quadObj);
}

void CelestialBodyController::drawCelestialBodies(float angle) {


	// Posiciona a câmera de acordo com posição x,y do mouse na janela

	this->initTextures();
	this->configureLights();

	float depth = 0;

	CelestialBody *celestialBody = celestialBodies->at(0);

	glDisable(GL_LIGHTING);

	float lightPos0[] = {0, 0, 0};

	glPushMatrix();
		glTranslated(0,0, depth);
//		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		glColor3f(1, 1, 1);
//		glutWireSphere(celestialBody->getScale(),5,5);
		glutWireTeapot(celestialBody->getScale());
	glPopMatrix();

//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glEnable(GL_LIGHTING);

	glColor3f(1, 0, 0);

	float s = 50.0;
	float matShine[] = { s };

	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	for (int i = 1; i < celestialBodies->size(); i++) {
		celestialBody = celestialBodies->at(i);

		glPushMatrix();
//			glRotatef(angle * celestialBody->getCoefRotation(), 0, 0, 1);
//			glTranslated(celestialBody->getCoordindate()->getX(),0,depth);
//			glRotatef(-angle * celestialBody->getCoefRotation(), 0, 0, 1);
//			glRotatef(angle * celestialBody->getCoefTranslation(), 0, 0, 1);
//			glutSolidSphere(celestialBody->getScale(),50,50);



//			glRotatef(angle * celestialBody->getCoefTranslation(), 0, 1, 0);
//			glTranslated(celestialBody->getCoordindate()->getX(),0,depth);
//			glRotatef(angle * celestialBody->getCoefRotation(), 0, 1, 0);
//			glutWireSphere(celestialBody->getScale(),5,5);

			Coordinate *coordinate = calculePosition(celestialBody->getCoordindate()->getX(),
					angle * celestialBody->getCoefTranslation());

//			glRotatef(angle * celestialBody->getCoefTranslation(), 0, 1, 0);
			glTranslated(coordinate->getX(), coordinate->getY(), coordinate->getZ());
			glPushMatrix();
				glRotatef(angle * celestialBody->getCoefRotation(), 0, 1, 0);
				glutWireSphere(celestialBody->getScale(),5,5);
			glPopMatrix();


			for (int j = 0; j < celestialBody->getCelestialBodies()->size(); j++) {
				CelestialBody *satellite = celestialBody->getCelestialBodies()->at(j);

				int count = rand() % 15 + 5;

				glPushMatrix();
//					glRotatef(angle * satellite->getCoefRotation(), 0, 0, 1);
//					glTranslated(satellite->getCoordindate()->getX(),0, 0);
//					glRotatef(-angle * satellite->getCoefRotation(), 0, 0, 1);
//					glRotatef((angle + j * DefaultParams::SATELLITE_DELAY * angle) * satellite->getCoefTranslation(), 0, 0, 1);
//					glutSolidSphere(satellite->getScale(), count, count);


//					glRotatef(angle * satellite->getCoefTranslation(), 0, 1, 0);
//					glTranslated(satellite->getCoordindate()->getX(),0, 0);
//					glRotatef(-angle * satellite->getCoefTranslation(), 0, 1, 0);
//					glRotatef((angle + j * DefaultParams::SATELLITE_DELAY * angle) * satellite->getCoefRotation(), 0, 1, 0);
//					glutWireSphere(satellite->getScale(), count, count);

				coordinate = calculePosition(satellite->getCoordindate()->getX(), angle * satellite->getCoefTranslation());

				glTranslated(coordinate->getX(), coordinate->getY(), coordinate->getZ());
//				glRotatef(-angle * satellite->getCoefTranslation(), 0, 1, 0);
//				glRotatef((angle + j * DefaultParams::SATELLITE_DELAY * angle) * satellite->getCoefRotation(), 0, 1, 0);
				glutWireSphere(satellite->getScale(), count, count);

				glPopMatrix();

			}

		glPopMatrix();

	}

	glDisable(GL_TEXTURE_2D);
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

		planet->setCoefRotation(planetRotation);
		planet->setCoefTranslation(planetTranslation);

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
		distancePlanet += val + planetScale;
	}

	cout << "veio aqui " << endl;
}

CameraCoordinate *CelestialBodyController::getCameraCoordinateBySatellitePosition(float angle) {

	if (celestialBodies != NULL) {

		CelestialBody *planet = celestialBodies->at(1);
		CelestialBody *satellite = NULL;

		double planetPosition[3];
		double satellitePosition[3];

//		double distanceCamera[] = { 2, 0, 2 };
		double distanceCamera = 3;

		double rouboNegativoSafadeza = -1;

		if (planet->getCelestialBodies() != NULL && planet->getCelestialBodies()->size() > 0) {
			satellite = planet->getCelestialBodies()->at(0);

//			planetPosition[0] = rouboNegativoSafadeza * sin( piRad * angle * planet->getCoefTranslation() ) *
//					planet->getCoordindate()->getX();
//			planetPosition[2] = rouboNegativoSafadeza * cos( piRad * angle * planet->getCoefTranslation() ) *
//					planet->getCoordindate()->getX();

			Coordinate *planetCoordinate = calculePosition(planet->getCoordindate()->getX(), angle * planet->getCoefTranslation());
			planetPosition[0] = planetCoordinate->getX();
			planetPosition[1] = planetCoordinate->getY();
			planetPosition[2] = planetCoordinate->getZ();

//			planetPosition[0] = rouboNegativoSafadeza * sin( piRad * angle * planet->getCoefTranslation() ) *
//					planet->getCoordindate()->getX();
//			planetPosition[2] = rouboNegativoSafadeza * cos( piRad * angle * planet->getCoefTranslation() ) *
//					planet->getCoordindate()->getX();

			double valCos = rouboNegativoSafadeza * cos( piRad * angle * satellite->getCoefTranslation() );
			double valSin = rouboNegativoSafadeza * sin( piRad * angle * satellite->getCoefTranslation() );


//			satellitePosition[0] = valSin *
//					satellite->getCoordindate()->getX();
//			satellitePosition[2] = valCos *
//					satellite->getCoordindate()->getX();
			Coordinate *satelliteCoordinate = calculePosition(satellite->getCoordindate()->getX(), angle * (satellite->getCoefTranslation()));
			satellitePosition[0] = satelliteCoordinate->getX() + distanceCamera * valSin;
			satellitePosition[1] = satelliteCoordinate->getY();
			satellitePosition[2] = satelliteCoordinate->getZ() + distanceCamera * valCos;

//			if (valCos >= 0) {
//				satellitePosition[0] += distanceCamera[0];
//			} else {
//				satellitePosition[0] -= distanceCamera[0];
//			}

//			satellitePosition[1] += distanceCamera[1];

//			if (valSin >= 0) {
//				satellitePosition[2] += distanceCamera[2];
//			} else {
//				satellitePosition[2] += distanceCamera[2];
//			}


			CameraCoordinate *cameraCoordinate = new CameraCoordinate();
//			cameraCoordinate->setEyeCoordinate(
//					new Coordinate(satellitePosition[0] + planetPosition[0], satellitePosition[1] + planetPosition[1], satellitePosition[2] + planetPosition[2]));
			cameraCoordinate->setEyeCoordinate(
								new Coordinate(satellitePosition[0] + planetPosition[0], satellitePosition[1] + planetPosition[1], satellitePosition[2] + planetPosition[2]));
			cameraCoordinate->setCenterCoordinate(
					new Coordinate(planetPosition[0], planetPosition[1], planetPosition[2]));

//			CameraCoordinate *cameraCoordinate = new CameraCoordinate();
//			cameraCoordinate->setEyeCoordinate(
//					new Coordinate(planetPosition[0], planetPosition[1], planetPosition[2]));
//			cameraCoordinate->setCenterCoordinate(
//					new Coordinate(planetPosition[0], planetPosition[1], planetPosition[2]));

			return cameraCoordinate;
		}

	}

	return NULL;
}

Coordinate *CelestialBodyController::calculePosition(double distance, double angle) {
	double position[3];

	double rouboNegativoSafadeza = -1;

	position[0] = rouboNegativoSafadeza * sin( piRad * angle ) *
			distance;
	position[2] = rouboNegativoSafadeza * cos( piRad * angle ) *
			distance;

	return new Coordinate(position[0], position[1], position[2]);
}
