/* Vector3 source file */

#include "vector3.hpp"
#include <math.h>

Vector3::Vector3(float x, float y, float z){

	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(Vector3 &v){

	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vector3::Vector3(Vector3 *v){

	this->x = v->x;
	this->y = v->y;
	this->z = v->z;
}


Vector3::~Vector3(){}

float Vector3::Magnitude(){
	return sqrt ((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}


/* Operators */
Vector3& Vector3::operator=(const Vector3& rhs){
	
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;

	return *this;
}

Vector3& Vector3::operator+(const Vector3& rhs){
	
	Vector3 *v = new Vector3(0.0f, 0.0f, 0.0f);

	v->x = this->x + rhs.x;
	v->y = this->y + rhs.y;
	v->z = this->z + rhs.z;

	return *v;
}

Vector3& Vector3::operator-(const Vector3& rhs){
	
	Vector3 *v = new Vector3(0.0f, 0.0f, 0.0f);

	v->x = this->x - rhs.x;
	v->y = this->y - rhs.y;
	v->z = this->z - rhs.z;

	return *v;
}

Vector3& Vector3::operator*(const float n) {
	
	Vector3 *v = new Vector3(0.0f, 0.0f, 0.0f);

	v->x = this->x * n;
	v->y = this->y * n;
	v->z = this->z * n;

	return *v;
}

Vector3& Vector3::operator/(const float n) {
	
	Vector3 *v = new Vector3(0.0f, 0.0f, 0.0f);

	v->x = this->x/n;
	v->y = this->y/n;
	v->z = this->z/n;

	return *v;
}