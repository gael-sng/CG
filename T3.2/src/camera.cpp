/*
	Gabriel Simmel Nascimento - 9050232
	Victor Luiz Roquete Forbes - 9293394
	Marcos Cesar Ribeiro de Camargo - 9278045
	José Augusto Noronha de Menezes Neto - 9293049
*/

#include <algorithm>
#include <cmath>
#include <GL/glut.h>

#include "camera.hpp"

using namespace std;

Camera::Camera(){
	this->speed = 0.3;
	this->rspeed = 1.5;
	this->gravity = 0.098;
	this->transform = new Transform(new Vector3(0.0, GROUND_LEVEL, 15.0), new Vector3(0.0, 0.0, 0.0), new Vector3(1.0, 1.0, 1.0));
}

Camera::~Camera(){
	delete transform;
}

void Camera::update(){
    glRotated(this->transform->rotation->x, 1.0, 0.0, 0.0);  // Rotate the camera around the x-axis.
    glRotated(this->transform->rotation->y, 0.0, 1.0, 0.0);  // Rotate the camera around the y-axis.
    glRotated(this->transform->rotation->z, 0.0, 0.0, 1.0);  // Rotate the camera around the z-axis.
    glTranslated(-this->transform->position->x, -this->transform->position->y, -this->transform->position->z); // Translate the screen to the camera position.
}

double to_rad(double theta){
	return (theta * M_PI) / 180.0;
}

void Camera::moveFoward(){
	this->transform->position->x += sin(to_rad(this->transform->rotation->y)) * this->speed;
	this->transform->position->z -= cos(to_rad(this->transform->rotation->y)) * this->speed;
	this->transform->position->y -= sin(to_rad(this->transform->rotation->x)) * this->speed;
}

void Camera::moveBack(){
	this->transform->position->x -= sin(to_rad(this->transform->rotation->y)) * this->speed;
	this->transform->position->z += cos(to_rad(this->transform->rotation->y)) * this->speed;
	this->transform->position->y += sin(to_rad(this->transform->rotation->x)) * this->speed;
}

void Camera::moveRight(){
	this->transform->position->x += cos(to_rad(this->transform->rotation->y)) * this->speed;
	this->transform->position->z += sin(to_rad(this->transform->rotation->y)) * this->speed;
}

void Camera::moveLeft(){
	this->transform->position->x -= cos(to_rad(this->transform->rotation->y)) * this->speed;
	this->transform->position->z -= sin(to_rad(this->transform->rotation->y)) * this->speed;
}

void Camera::lookLeft(){
    this->transform->rotation->y -= this->rspeed;
}

void Camera::lookRight(){
    this->transform->rotation->y += this->rspeed;
}

void Camera::pitchUp(){
    this->transform->rotation->x -= this->rspeed;
    checkRotation();
}

void Camera::pitchDown(){
    this->transform->rotation->x += this->rspeed;
    checkRotation();
}

void Camera::checkRotation(){
	this->transform->rotation->x = min(this->transform->rotation->x, 90.0);
	this->transform->rotation->x = max(this->transform->rotation->x, -90.0);
}