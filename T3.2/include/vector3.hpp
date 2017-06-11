/*	Classe que implementa uma estrutura de dados frequentemente usada em ambientes 3D.
	Representa um vetor de 3 doubles e operações vetoriais básicas.
*/

#pragma once

#include <cmath>

class Vector3{
public:
	double x, y, z;

	// Empty constructor.
	Vector3(){
		this->x = this->y = this->z = 0.0;
	}

	// Constructor.
	Vector3(double x, double y, double z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// Constructor.
	Vector3(Vector3* b){
		this->x = b->x;
		this->y = b->y;
		this->z = b->z;
	}

	// Vector3 sum.
	Vector3 operator + (const Vector3 &b) const{
		return Vector3(this->x + b.x, this->y + b.y, this->z + b.z);
	}

	// Vector3 sum (cumulative).
	Vector3 &operator += (const Vector3 &b){
		this->x += b.x;
		this->y += b.y;
		this->z += b.z;

		return *this;
	}

	// Vector3 subtraction.
	Vector3 operator - (const Vector3 &b) const{
		return Vector3(this->x - b.x, this->y - b.y, this->z - b.z);
	}

	// Negative Vector3.
	Vector3 operator - () const{
		return Vector3(-this->x, -this->y, -this->z);
	}

	// Vector3 subtraction (cumulative).
	Vector3 &operator -= (const Vector3 &b){
		this->x -= b.x;
		this->y -= b.y;
		this->z -= b.z;

		return *this;
	}

	// Vector3 product by scalar.
	Vector3 operator * (double a){
		return Vector3(this->x * a, this->y * a, this->z * a);
	}

	// Vector3 product by scalar (cumulative).
	Vector3 &operator *= (double a){
		this->x *= a;
		this->y *= a;
		this->z *= a;

		return *this;
	}

	// Vector3 division by scalar.
	Vector3 operator / (double a){
		return Vector3(this->x / a, this->y / a, this->z / a);
	}

	// Vector3 division by scalar (cumulative).
	Vector3 &operator /= (double a){
		this->x /= a;
		this->y /= a;
		this->z /= a;

		return *this;
	}

	// Dot product.
	double operator * (const Vector3 &b) const{
		return this->x * b.x + this->y * b.y + this->z * b.z;
	}

	// Cross product.
	Vector3 operator ^ (const Vector3 &b) const{
		return Vector3(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
	}

	// Cross product (cumulative).
	Vector3 &operator ^= (const Vector3 &b){
		double new_x, new_y, new_z;

		new_x = this->y * b.z - this->z * b.y;
		new_y = this->z * b.x - this->x * b.z;
		new_z = this->x * b.y - this->y * b.x;

		this->x = new_x;
		this->y = new_y;
		this->z = new_z;

		return *this;
	}

	// Norm.
	double operator ! () const{
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	// Compare function.
	bool operator < (const Vector3 &b) const{
		if (this->x == b.x){
			if (this->y == b.y){
				return this->z < b.z;
			}

			return this->y < b.y;
		}

		return this->x < b.x;
	}

	// Compare function.
	bool operator > (const Vector3 &b) const{
		return b < *this;
	}

	// Compare function.
	bool operator == (const Vector3 &b) const{
		return this->x == b.x and this->y == b.y and this->z == b.z;
	}

	// Compare function.
	bool operator != (const Vector3 &b) const{
		return !(*this == b);
	}
};
