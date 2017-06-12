/*
	Gabriel Simmel Nascimento - 9050232
	Victor Luiz Roquete Forbes - 9293394
	Marcos Cesar Ribeiro de Camargo - 9278045
	José Augusto Noronha de Menezes Neto - 9293049
*/

#include <cmath>
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

#define N_OBJECTS 9
#define CAMERA_DIST 4

#define FPS 60
#define DELTA_MILI_TIME (1000 / FPS)// tempo entre frames em milisecundos FIXO

#define TO_RAD (M_PI / 180.0)

typedef int OBJECT_TYPE;

/* Each scene object contains a reference to it's transform properties
and a OBJECT_TYPE, which is used to call the correct drawing function defined in draw.hpp */
struct sceneObject{
	Transform *transform;
	OBJECT_TYPE type;
};

enum ascii_codes{
	ASCII_NUL,
	ASCII_SOH,
	ASCII_STX,
	ASCII_ETX,
	ASCII_EOT,
	ASCII_ENQ,
	ASCII_ACK,
	ASCII_BEL,
	ASCII_BS,
	ASCII_HT,
	ASCII_LF,
	ASCII_VT,
	ASCII_FF,
	ASCII_CR,
	ASCII_SO,
	ASCII_SI,
	ASCII_DLE,
	ASCII_DC1,
	ASCII_DC2,
	ASCII_DC3,
	ASCII_DC4,
	ASCII_NAK,
	ASCII_SYN,
	ASCII_ETB,
	ASCII_CAN,
	ASCII_EM,
	ASCII_SUB,
	ASCII_ESC,
	ASCII_FS,
	ASCII_GS,
	ASCII_RS,
	ASCII_US,
	ASCII_DEL = 127
};

int g_WindowHandle; // Real declaration of global window handler
int selectedObject = 0; // object that will handle transformations
bool keys[255] = {0}; // keypress state
bool skeys[255] = {0}; // special keypress state

Camera *cam;

//list of scene objects.
sceneObject objects[N_OBJECTS];
double dist = 9.0f;

void myInit(){
	double x, y, z;
	int i, j;

	cam = new Camera();

	// Object 0 is a Teapot at (0, 0, 0).
	objects[0].transform = new Transform(0.0, -1.0, -5.0, 0.0, 180.0, 0.0, -0.9, -0.9, -0.9);
	objects[0].type = TEAPOT;

	// Creating other objects.
	for (i = 0; i < (1 << 3); i++){
		x = ((1 << 0) & i) ? dist : -dist;
		y = ((1 << 1) & i) ? dist : -dist;
		z = ((1 << 2) & i) ? dist : -dist;

		objects[i + 1].transform = new Transform(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		objects[i + 1].type = (rand() % 2) + 1;
	}
}

// function that deletes "camera" and "sceneObject" objects
void myCleanup(){
	int i;

	delete cam;

	for (i = 0; i < 3; i++){
		delete objects[i].transform;
	}
}

// function that processes normal button presses (such as 'w', 'a', 's' and 'd')
void processKeys(){

	// Movement
	if(keys['w']){
		cam->moveFoward();
	}
	
	if(keys['s']){
		cam->moveBack();
	}
	
	if(keys['a']){
		cam->moveLeft();
	}
	
	if(keys['d']){
		cam->moveRight();
	}

	if(skeys[GLUT_KEY_UP]){
		cam->pitchUp();
	}
	
	if(skeys[GLUT_KEY_DOWN]){
		cam->pitchDown();
	}
	
	if(skeys[GLUT_KEY_LEFT]){
		cam->lookLeft();
	}
	
	if(skeys[GLUT_KEY_RIGHT]){
		cam->lookRight();
	}
	// Cleanup glut before exiting
	if(keys[ASCII_ESC]) glutDestroyWindow(g_WindowHandle), myCleanup(), exit(0);
}

// GlutIdleFunc callback. Processes keys and redraw scene
void Update(int step){
	glutTimerFunc((unsigned int)DELTA_MILI_TIME, Update, step);
	
	processKeys();
	
	glutPostRedisplay();
}

// GlutDisplayFunc callback. Clears screen and draws the scene
void Render(){
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	//selectedObject - TEAPOT == 0 ? drawTeapot(objects[i].transform, true): drawTeapot(objects[i].transform, false);

	//selectedObject - TEAPOT == 0 ? drawTeapot(objects[0].transform, true): drawTeapot(objects[0].transform, false);
	drawAirplane(objects[0].transform, true);
	glLoadIdentity();

	// Set the camera
	cam->update();

    // Draw ground
    drawGround(-dist);

    // Draws scene objects
    for(int i = 1; i < N_OBJECTS; i++){

		glPushMatrix();

    	switch(objects[i].type){
    	case TEAPOT:
    		selectedObject - TEAPOT == 0 ? drawTeapot(objects[i].transform, true): drawTeapot(objects[i].transform, false);
    		break;

    	case TORUS:
    		selectedObject - TORUS == 0 ? drawTorus(objects[i].transform, true): drawTorus(objects[i].transform, false);
    		break;

    	case CUBE:
    		selectedObject - CUBE == 0 ? drawCube(objects[i].transform, true): drawCube(objects[i].transform, false);
    		break;

		default:
			break;
		}

		glPopMatrix();
    }

	//swap buffers, outputting all drawings done
	glutSwapBuffers();
}

// glutReshapeFunc callback. Corrects the aspect ratio when the window size changes
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;

	float _w = w, _h = h;

	float ratio = _w/_h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// sets key presses when some key is pressed
void keyboardUp(unsigned char key, int x, int y){ keys[key] = false; }
void keyboardDown(unsigned char key, int x, int y){keys[key] = true; }

void specialUp(int key, int x, int y){ skeys[key] = false; }
void specialDown(int key, int x, int y){ skeys[key] = true; }