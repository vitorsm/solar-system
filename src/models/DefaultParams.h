/*
 * Params.h
 *
 *  Created on: 29 de mai de 2018
 *      Author: vitor
 */

#ifndef DEFAULTPARAMS_H_
#define DEFAULTPARAMS_H_

class DefaultParams {
public:
	DefaultParams();
	virtual ~DefaultParams();

	// Quantidade de planetas padrão
	static int DEFAULT_PLANETS_AMOUNT;

	// Tempo para atualização da cena
	static int UPDATE_TIME;

	// Atraso de um satelite para outro
	static float SATELLITE_DELAY;
};

#endif /* DEFAULTPARAMS_H_ */
