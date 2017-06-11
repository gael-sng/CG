#include <math.h>
#include <GL/glut.h>

#include "camera.hpp"

Camera::Camera(){
	speed = 0.3f;
	gravity = 0.098f;

	transform = new Transform(new Vector3(0.0, GROUND_LEVEL, 15.0), new Vector3(0.0, 0.0, 0.0), new Vector3(1.0, 1.0, 1.0));
}

Camera::~Camera(){
	delete transform;
}


void Camera::update(){
    glRotated(transform->rotation->x, 1.0, 0.0, 0.0);  //rotate our camera on the  x-axis (left and right)
    glRotated(transform->rotation->y, 0.0, 1.0, 0.0);  //rotate our camera on the  y-axis (up and down)
    glRotated(transform->rotation->z, 0.0, 0.0, 1.0);  //rotate our camera on the  z-axis (dunno)
    glTranslated(-transform->position->x, -transform->position->y, -transform->position->z); //translate the screen to the position of our camera
}

double to_rad(double theta){
	return (theta * M_PI) / 180.0;
}

void Camera::moveFoward(){
	transform->position->x += sin(to_rad(transform->rotation->y)) * speed;
	transform->position->z -= cos(to_rad(transform->rotation->y)) * speed;
	transform->position->y -= sin(to_rad(transform->rotation->x)) * speed;
}

void Camera::moveBack(){
	transform->position->x -= sin(to_rad(transform->rotation->y)) * speed;
	transform->position->z += cos(to_rad(transform->rotation->y)) * speed;
	transform->position->y += sin(to_rad(transform->rotation->x)) * speed;
}

void Camera::moveRight(){
	transform->position->x += cos(to_rad(transform->rotation->y)) * speed;
	transform->position->z += sin(to_rad(transform->rotation->y)) * speed;
}

void Camera::moveLeft(){
	transform->position->x -= cos(to_rad(transform->rotation->y)) * speed;
	transform->position->z -= sin(to_rad(transform->rotation->y)) * speed;
}

void Camera::lookLeft(){
    transform->rotation->y -= 1.0f;
}

void Camera::lookRight(){
    transform->rotation->y += 1.0f;
}

void Camera::pitchUp(){
    transform->rotation->x -= 1.0f;
    checkRotation();
}

void Camera::pitchDown(){
    transform->rotation->x += 1.0f;
    checkRotation();
}

void Camera::checkRotation(){
	if(transform->rotation->x > 90) transform->rotation->x = 90;
	if(transform->rotation->x < -90) transform->rotation->x = -90;
}