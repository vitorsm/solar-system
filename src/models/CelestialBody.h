	/*
 * CelestialBody.h
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#ifndef CELESTIALBODY_H_
#define CELESTIALBODY_H_

#include <vector>
#include "Coordinate.h"

using namespace std;

class CelestialBody {
public:
	CelestialBody();
	virtual ~CelestialBody();

	void setScale(float scale);
	float getScale();
	void setCoordinate(Coordinate *coordinate);
	Coordinate *getCoordindate();
	vector<CelestialBody*> *getCelestialBodies();
	void setCoefTranslation(float coefTranslation);
	float getCoefTranslation();
	void setCoefRotation(float coefRotation);
	float getCoefRotation();
	void addCelestialBody(CelestialBody *celestialBody);
private:
	float scale;
	Coordinate *coordinate;
	vector<CelestialBody*> *celestialBodies;
	float coefTranslation;
	float coefRotation;
};

#endif /* CELESTIALBODY_H_ */
