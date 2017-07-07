/*
	Gabriel Simmel Nascimento - 9050232
	Victor Luiz Roquete Forbes - 9293394
	Marcos Cesar Ribeiro de Camargo - 9278045
	José Augusto Noronha de Menezes Neto - 9293049
*/

#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <GL/glut.h>

#include "Vector3.hpp"
#include "camera.hpp"
#include "callbacks.hpp"
#include "draw.hpp"
#include "transform.hpp"

// Defining scene objects types
#define TEAPOT 0
#define TORUS 1
#define CUBE 2

#define NEXT 1
#define PREVIOUS -1
#define ASCII_ESC 27

#define N_OBJECTS 8
#define CAMERA_DIST 4

#define FPS 60
#define DELTA_MILI_TIME (1000 / FPS)// tempo entre frames em milisecundos FIXO

#define TO_RAD (M_PI / 180.0)

/* Each scene object contains a reference to it's transform properties
and a int, which is used to call the correct drawing function defined in draw.hpp */
struct Entity{
	Transform *transform;
	int type;
};

int g_WindowHandle; // Real declaration of global window handler
bool keys[256] = {0}; // keypress state
bool skeys[256] = {0}; // special keypress state

Camera *cam;
Entity Player;

//list of scene objects.
Entity objects[N_OBJECTS];
double dist = 50.0f;
double offset = 25.0f;

void myInit(){
	double x, y, z;
	int i, j;

	cam = new Camera();

	Player.transform = new Transform(0.0, -1.3, -5.0, 7.0, 180.0, 0.0, -0.9, -0.9, -0.9);
	Player.type = TEAPOT;

	// Creating other objects.
	for (i = 0; i < (1 << 3); i++){
		x = ((1 << 0) & i) ? offset : -offset;
		y = ((1 << 1) & i) ? offset : -offset;
		z = ((1 << 2) & i) ? offset : -offset;

		objects[i].transform = new Transform(x, y, z, 90.0f, 0.0f, (GLfloat)(rand() % 180), 5.0, 5.0, 5.0);
		objects[i].type = TORUS;
	}
}

// function that deletes "camera" and "Entity" objects
void myCleanup(){
	int i;

	delete cam;

	for (i = 0; i < N_OBJECTS; i++){
		delete objects[i].transform;
	}
}

// Function that processes normal button presses (such as 'w', 'a', 's' and 'd')
void processKeys(){
	// Movement
	if (keys['w'] or keys['W']){
		cam->moveFoward();
	}
	
	if (keys['s'] or keys['S']){
		cam->moveBack();
	}
	
	if (keys['a'] or keys['A']){
		cam->moveLeft();
	}
	
	if (keys['d'] or keys['D']){
		cam->moveRight();
	}

	if (skeys[GLUT_KEY_DOWN]){
		cam->pitchUp();
	}
	
	if (skeys[GLUT_KEY_UP]){
		cam->pitchDown();
	}
	
	if (skeys[GLUT_KEY_LEFT]){
		cam->lookLeft();
	}
	
	if (skeys[GLUT_KEY_RIGHT]){
		cam->lookRight();
	}

	// Cleanup glut before exiting
	if (keys[ASCII_ESC]){
		glutDestroyWindow(g_WindowHandle);
		myCleanup();
		exit(0);
	}
}

#define max_angle  15.0f
#define angle_Speed 1.0f

void Play(){
	// Inclinando para a direita ou para a esquerda.
	if (skeys[GLUT_KEY_RIGHT] and Player.transform->rotation->z < max_angle){
		Player.transform->rotation->z += angle_Speed;
	}
	if (not skeys[GLUT_KEY_RIGHT] and Player.transform->rotation->z > 0.0f){
		Player.transform->rotation->z -= angle_Speed;
	}
	if (skeys[GLUT_KEY_LEFT] and Player.transform->rotation->z > -max_angle){
		Player.transform->rotation->z -= angle_Speed;
	}
	if (not skeys[GLUT_KEY_LEFT] and Player.transform->rotation->z < 0.0f){
		Player.transform->rotation->z += angle_Speed;
	}

	// Inclinando para frente ou para trás.
	if (skeys[GLUT_KEY_DOWN] and Player.transform->rotation->x < max_angle){
		Player.transform->rotation->x += angle_Speed;
	}
	if (not skeys[GLUT_KEY_DOWN] and Player.transform->rotation->x > 0.0f){
		Player.transform->rotation->x -= angle_Speed;
	}
	if (skeys[GLUT_KEY_UP] and Player.transform->rotation->x > -max_angle){
		Player.transform->rotation->x -= angle_Speed;
	}
	if (not skeys[GLUT_KEY_UP] and Player.transform->rotation->x < 0.0f){
		Player.transform->rotation->x += angle_Speed;
	}
}

// GlutIdleFunc callback. Processes keys and redraw scene
void Update(int step){
	glutTimerFunc((unsigned int)DELTA_MILI_TIME, Update, step);
	
	Play();

	processKeys();
	
	glutPostRedisplay();
}

// GlutDisplayFunc callback. Clears screen and draws the scene
void Render(){
	int i;

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	drawAirplane(Player.transform);
	glLoadIdentity();

	// Set the camera
	cam->update();

    // Draw ground and sky
    drawGround(-dist);
    drawSky();
    drawAxis();

    // Draws scene objects
    for (i = 0; i < N_OBJECTS; i++){
		glPushMatrix();

    	drawTorus(objects[i].transform);

		glPopMatrix();
    }

	//swap buffers, outputting all drawings done
	glutSwapBuffers();
}

// glutReshapeFunc callback. Corrects the aspect ratio when the window size changes
void changeSize(int w, int h){
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (!h){
		h = 1;
	}

	float ratio = (float)w / (float)h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 200.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// sets key presses when some key is pressed
void keyboardUp(unsigned char key, int x, int y){
	keys[key] = false;
}
void keyboardDown(unsigned char key, int x, int y){
	keys[key] = true;
}

void specialUp(int key, int x, int y){
	skeys[key] = false;
}
void specialDown(int key, int x, int y){
	skeys[key] = true;
}