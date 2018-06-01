/*
 * CameraCoordinate.h
 *
 *  Created on: 1 de jun de 2018
 *      Author: vitor
 */

#ifndef CAMERACOORDINATE_H_
#define CAMERACOORDINATE_H_

#include "Coordinate.h"

class CameraCoordinate {
public:
	CameraCoordinate();
	virtual ~CameraCoordinate();

	void setEyeCoordinate(Coordinate *coordinate);
	Coordinate *getEyeCoordinate();
	void setCenterCoordinate(Coordinate *coordinate);
	Coordinate *getCenterCoordinate();
	void setUpCoordinate(Coordinate *coordinate);
	Coordinate *getUpCoordinate();

private:
	// Coordenadas da posicao da camera
	Coordinate *eyeCoordinate;
	// Coordenadas de onde a camera esta olhando
	Coordinate *centerCoordinate;
	// Coordenadas do vetor up
	Coordinate *upCoordinate;
};

#endif /* CAMERACOORDINATE_H_ */
