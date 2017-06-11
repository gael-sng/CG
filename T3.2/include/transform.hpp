/* Transform header file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Augusto Monteiro 			-	9293095

*/

#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "vector3.hpp"

class Transform {

public:

	Vector3 *position;
	Vector3 *rotation;
	Vector3 *scale;

	Transform();
	Transform(Vector3& position, Vector3& rotation, Vector3& scale);
	Transform(Vector3 *position, Vector3 *rotation, Vector3 *scale);
	Transform(float px, float py, float pz, 
					float rx, float ry, float rz, 
					float sx, float sy, float sz);
	virtual ~Transform();
};

#endif

