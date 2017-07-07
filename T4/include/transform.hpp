/*
	Gabriel Simmel Nascimento - 9050232
	Victor Luiz Roquete Forbes - 9293394
	Marcos Cesar Ribeiro de Camargo - 9278045
	José Augusto Noronha de Menezes Neto - 9293049
*/

#pragma once

#include "Vector3.hpp"

class Transform{
public:
	Vector3 *position, *rotation, *scale;

	Transform();
	Transform(Vector3 *, Vector3 *, Vector3 *);
	Transform(double, double, double, double, double, double, double, double, double);
	virtual ~Transform();
};
