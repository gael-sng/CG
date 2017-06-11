#include <math.h>
#include <GL/glut.h>

#include "Vector3.hpp"
#include "camera.hpp"
#include "callbacks.hpp"
#include "draw.hpp"
#include "transform.hpp"

//defining scene objects types
#define TEAPOT 0
#define TORUS 1
#define CUBE 2
#define NEXT 1
#define PREVIOUS -1

#define N_OBJECTS 9
#define CAMERA_DIST 4

#define FPS 60
#define DELTA_MILI_TIME (1000/FPS)// tempo entre frames em milisecundos FIXO



#define TO_RAD (M_PI/180.0)



typedef int OBJECT_TYPE;

/* Each scene object contains a reference to it's transform properties
and a OBJECT_TYPE, which is used to call the correct drawing function defined in draw.hpp*/
typedef struct _sceneObject{
	Transform* transform;
	OBJECT_TYPE type;
} sceneObject;

enum ascii_codes {

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

Camera* cam;

//list of scene objects.
sceneObject objects[N_OBJECTS];
double dist = 9.0f;
void myInit(){

	cam = new Camera();

	//object 1 is a Torus located in (0,0,0)
	objects[0].transform = new Transform(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects[0].type = TEAPOT;

	//object 1 is a Torus located in (0,0,0)
	objects[1].transform = new Transform(dist, dist, dist, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects[1].type = CUBE;

	//object 1 is a Torus located in (0,0,0)
	objects[2].transform = new Transform(-dist, dist, dist, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects[2].type = TORUS;

	//object 1 is a Torus located in (0,0,0)
	objects[3].transform = new Transform(dist, -dist, dist, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects[3].type = CUBE;

	//object 1 is a Torus located in (0,0,0)
	objects[4].transform = new Transform(dist, dist, -dist, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects[4].type = TORUS;

	//object 1 is a Torus located in (0,0,0)
	objects[5].transform = new Transform(-dist, -dist, dist, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects[5].type = CUBE;

	//object 1 is a Torus located in (0,0,0)
	objects[6].transform = new Transform(dist, -dist, -dist, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects[6].type = TORUS;
	
	//object 1 is a Torus located in (0,0,0)
	objects[7].transform = new Transform(-dist, dist, -dist, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects[7].type = CUBE;
	
	//object 1 is a Torus located in (0,0,0)
	objects[8].transform = new Transform(-dist, -dist, -dist, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects[8].type = TORUS;

}

// function that deletes "camera" and "sceneObject" objects
void myCleanup(){
	delete cam;

	for(int i = 0; i < 3; i++){
		delete objects[i].transform;
	}
}

// function that processes normal button presses (such as 'w', 'a', 's' and 'd')
void processKeys() {

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

void playerMove(){
	Transform* t = objects[0].transform; 
	t->position->x = cam->transform->position->x + (sin(TO_RAD * cam->transform->rotation->y) * CAMERA_DIST);
	t->position->x = cam->transform->position->x - (cos(TO_RAD * cam->transform->rotation->y) * CAMERA_DIST);
	t->position->x = cam->transform->position->x - (sin(TO_RAD * cam->transform->rotation->x) * CAMERA_DIST);
	
	t->rotation->x = cam->transform->rotation->x;
	t->rotation->y = cam->transform->rotation->y;
	t->rotation->z = cam->transform->rotation->z;
}

// GlutIdleFunc callback. Processes keys and redraw scene
void Update(int step){
	glutTimerFunc((unsigned int)DELTA_MILI_TIME, Update, step);
	
	processKeys();

	playerMove();
	
	glutPostRedisplay();
}

// GlutDisplayFunc callback. Clears screen and draws the scene
void Render(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	cam->update();

    // Draw ground
    drawGround(-dist);

    // Draws scene objects
    for(int i = 0; i < N_OBJECTS; i++){

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
