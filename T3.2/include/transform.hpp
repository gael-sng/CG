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
