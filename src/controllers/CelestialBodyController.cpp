/*
 * CelestialBodyController.cpp
 *
 *  Created on: 30 de mai de 2018
 *      Author: vitor
 */

#include "CelestialBodyController.h"

CelestialBodyController::CelestialBodyController() {

	srand(time(NULL));

}

CelestialBodyController::~CelestialBodyController() {
	// TODO Auto-generated destructor stub
}


void CelestialBodyController::drawCelestialBodies(float angle) {

	float depth = -90;

	CelestialBody *celestialBody = celestialBodies->at(0);

	glColor3f(1, 0.7, 0);

	glPushMatrix();
		glTranslated(0,0,-50);
//		glRotated(60,1,0,0);
		glutWireSphere(celestialBody->getScale(),50,50);
	glPopMatrix();

	for (int i = 1; i < celestialBodies->size(); i++) {
		celestialBody = celestialBodies->at(i);

		glPushMatrix();
			glRotatef(angle * celestialBody->getCoefRotation(), 0, 0, 1);
			glTranslated(celestialBody->getCoordindate()->getX(),0,depth);
			glRotatef(-angle * celestialBody->getCoefRotation(), 0, 0, 1);
			glRotatef(angle * celestialBody->getCoefTranslation(), 0, 0, 1);
			glutWireSphere(celestialBody->getScale(),50,50);

			for (int j = 0; j < celestialBody->getCelestialBodies()->size(); j++) {
				CelestialBody *satellite = celestialBody->getCelestialBodies()->at(j);

				glPushMatrix();
//					glTranslated(celestialBody->getCoordindate()->getX(),0,0);
					glRotatef(angle * satellite->getCoefRotation(), 0, 0, 1);
					glTranslated(satellite->getCoordindate()->getX(),0, 0);
					glRotatef(-angle * satellite->getCoefRotation(), 0, 0, 1);
					glRotatef((angle + j * DefaultParams::SATELLITE_DELAY * angle) * satellite->getCoefTranslation(), 0, 0, 1);
					glutWireSphere(satellite->getScale(),5,5);
				glPopMatrix();
			}

		glPopMatrix();

	}
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

		Coordinate *coordinate = new Coordinate(distancePlanet, 0, 0);
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

			planet->addCelestialBody(satellite);
		}

		float val = rand() % ((int) initialDistancePlanet * 1000) / 1000.0;
		distancePlanet += val + planetScale;
	}
}
