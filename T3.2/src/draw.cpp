/* Drawing source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Augusto Monteiro 		-	9293095

*/


#include <math.h>
#include <GL/glut.h>

#include "draw.hpp"

#define HIGHLIGHTED 0.5f, 0.2f, 0.9f
#define NOT_HIGHLIGHTED 0.3f, 0.3f, 0.3f

//color array
GLfloat color[] = {0.0f, 0.0f, 0.0f, 1.0f};

void applyTransform(Transform* obj){
	glTranslatef(obj->position->x, obj->position->y + 0.7, obj->position->z);
	glScalef(obj->scale->x + 1, obj->scale->y + 1, obj->scale->z + 1);

	glRotatef(obj->rotation->x, 1.0f, 0.0f, 0.0f);
	glRotatef(obj->rotation->y, 0.0f, 1.0f, 0.0f);
	glRotatef(obj->rotation->z, 0.0f, 0.0f, 1.0f);
}

void drawTorus(Transform* torus, bool selected){

	applyTransform(torus);

	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 1.2f;
	color[2] = 1.3f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	glRotatef(90,1,0,0);

	selected? glColor3f(HIGHLIGHTED): glColor3f(NOT_HIGHLIGHTED);
	glutSolidTorus(0.4f, 0.7f, 20, 20);
}

void drawCube(Transform* cube, bool selected){

	applyTransform(cube);

	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 1.2f;
	color[2] = 1.3f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);


	selected? glColor3f(HIGHLIGHTED): glColor3f(NOT_HIGHLIGHTED);
	glutSolidCube(1.5f);

}


void drawSky(){
	glColor3f(0.0f,0.0f,1.0f);
	glutSolidTeapot(70.0f);
}

void drawGround(double hight){
	glBegin(GL_QUADS);

	glColor3f(255.0f, 255.0f, 255.0f);
	glVertex3f(-30.0f, hight, -30.0f);

	glColor3f(255.0f, 0.0f, 255.0f);
	glVertex3f(-30.0f, hight,  30.0f);

	glColor3f(255.0f, 255.0f, 0.0f);
	glVertex3f( 30.0f, hight,  30.0f);

	glColor3f(0.0f, 255.0f, 255.0f);
	glVertex3f( 30.0f, hight, -30.0f);

	glEnd();

	drawSky();
}


void drawTeapot(Transform* teapot, bool selected) {

	glPushMatrix();

	// Apllies transformations
	applyTransform(teapot);

	// Draws obj
	selected? glColor3f(HIGHLIGHTED): glColor3f(NOT_HIGHLIGHTED);
	glutSolidTeapot(0.7f);

	glPopMatrix();

}