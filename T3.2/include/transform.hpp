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
	Transform(Vector3 *position, Vector3 *rotation, Vector3 *scale);
	Transform(double px, double py, double pz, double rx, double ry, double rz, double sx, double sy, double sz);
	virtual ~Transform();
};
