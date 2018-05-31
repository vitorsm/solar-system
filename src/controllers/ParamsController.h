/*
 * ParamsController.h
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#ifndef PARAMSCONTROLLER_H_
#define PARAMSCONTROLLER_H_

#include "../models/Params.h"
#include "../models/DefaultParams.h"

class ParamsController {
public:
	ParamsController();
	virtual ~ParamsController();
	void drawParamsScreen();

	Params *getParams();
private:
	Params *params;

};

#endif /* PARAMSCONTROLLER_H_ */
