/*
 * Coordinate.h
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

class Coordinate {
public:
	Coordinate(float x, float y, float z);
	virtual ~Coordinate();

	float getX();
	float getY();
	float getZ();

private:
	float x;
	float y;
	float z;
};

#endif /* COORDINATE_H_ */
