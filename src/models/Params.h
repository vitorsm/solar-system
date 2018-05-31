/*
 * Params.h
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#ifndef PARAMS_H_
#define PARAMS_H_

class Params {
public:
	Params();
	virtual ~Params();

	void setPlanetsAmount(int planetsAmount);
	int getPlanetsAmount();
	void setArtificialSatelliteAmount(int artificialSatelliteAmount);
	int getArtificialSatelliteAmount();
	void setNaturalSatelliteAmount(int naturalSatelliteAmount);
	int getNaturalSatelliteAmount();


private:
	int planetsAmount;
	int artificialSatelliteAmount;
	int naturalSatelliteAmount;
};

#endif /* PARAMS_H_ */
