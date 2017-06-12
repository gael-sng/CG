/*
	Gabriel Simmel Nascimento - 9050232
	Victor Luiz Roquete Forbes - 9293394
	Marcos Cesar Ribeiro de Camargo - 9278045
	José Augusto Noronha de Menezes Neto - 9293049
*/

#pragma once

#include "transform.hpp"
#include "Vector3.hpp"

#define GROUND_LEVEL 1.0

class Camera{
public:
	double speed, rspeed;
	Transform *transform;

	Camera();
	virtual ~Camera();

	void checkRotation();
	void update();
	void moveFoward();
	void moveBack();
	void moveRight();
	void moveLeft();
	void lookLeft();
	void lookRight();
	void pitchUp();
	void pitchDown();
};
