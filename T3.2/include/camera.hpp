#pragma once

#include "transform.hpp"
#include "Vector3.hpp"

#define GROUND_LEVEL 1.0

#define X 0
#define Y 1
#define Z 2

class Camera{
public:
	double speed, gravity;
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
