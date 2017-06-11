/*	Classe que implementa uma estreutura de dados 
	freqeuntemente usada em ambientes 3D que é o vector3 
	que é basicamente um vetor de 3 numeros floats e operações de somar multiplicar subtrair etc.
	
	créditos classe implementada inicialmente por:
	Giovanna Oliveira Guimarães
	Lucas Alexandre Soares
	Rafael Augusto Monteiro
	
	modificada por nos:
	Gabriel Simmel Nascimento
	Victor Roquete Forbes
	Marco Camargo
*/

#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_
;
class Vector3 {

public:

	float x;
	float y;
	float z;

	Vector3(float x, float y, float z);
	Vector3(Vector3 &v);
	Vector3(Vector3 *v);
	virtual ~Vector3();

	float Magnitude();

	Vector3& operator=(const Vector3& rhs);

	Vector3& operator+(const Vector3& rhs);
	Vector3& operator-(const Vector3& rhs);
	Vector3& operator*(const float rhs);
	Vector3& operator/(const float rhs);
};

#endif

