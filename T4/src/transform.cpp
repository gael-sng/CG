/* 
	Gabriel Simmel Nascimento - 9050232
	Victor Luiz Roquete Forbes - 9293394
	Marcos Cesar Ribeiro de Camargo - 9278045
	José Augusto Noronha de Menezes Neto - 9293049
*/

#include "transform.hpp"

Transform::Transform(){
	this->position = new Vector3(0.0f, 0.0f, 0.0f);
	this->rotation = new Vector3(0.0f, 0.0f, 0.0f);
	this->scale = new Vector3(0.0f, 0.0f, 0.0f);
}

Transform::Transform(Vector3 *position, Vector3 *rotation, Vector3 *scale){
	this->position = new Vector3(position);
	this->rotation = new Vector3(rotation);
	this->scale = new Vector3(scale);
}

Transform::Transform(double px, double py, double pz, double rx, double ry, double rz, double sx, double sy, double sz){
	this->position = new Vector3(px, py, pz);
	this->rotation = new Vector3(rx, ry, rz);
	this->scale = new Vector3(sx, sy, sz);
}

Transform::~Transform(){
	delete this->position;
	delete this->rotation;
	delete this->scale;
}