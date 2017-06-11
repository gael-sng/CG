/**********************************************************************
	
  camera with OpenGL

  March, 13th, 2003

  This tutorial was written by Philipp Crocoll
  Contact: 
	philipp.crocoll@web.de
	www.codecolony.de

  Every comment would be appreciated.

  If you want to use parts of any code of mine:
	let me know and
	use it!

**********************************************************************
ESC: exit

CAMERA movement:
w : forwards
s : backwards
a : turn left
d : turn right
x : turn up
y : turn down
v : strafe right
c : strafe left
r : move up
f : move down
m/n : roll

***********************************************************************/

#include <GL/glut.h>
#include "camera.h"
#include "KeyBoard.cpp"


#define ShowUpvector
#define FPS 30
#define DELTA_MILI_TIME (1000.0f/FPS) // tempo entre frames em milisecundos FIXO

CCamera camera;
KeyBoard keyBoard;


void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ){
	glBegin(GL_LINES);
	for (int xc = 0; xc < LinesX; xc++){
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / 2.0);
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / -2.0);
	}

	for (int zc = 0; zc < LinesX; zc++){
		glVertex3f(	size / 2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
		glVertex3f(	size / -2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
	}

	glEnd();
}

void reshape(int x, int y){
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  //Use the whole window for rendering
}

void Update(){
	if(keyBoard.a){
		camera.RotateY(5.0);
	}		
	if(keyBoard.d){
		camera.RotateY(-5.0);
	}		
	if(keyBoard.w){
		camera.MoveForward( -0.1 ) ;
	}		
	if(keyBoard.s){
		camera.MoveForward( 0.1 ) ;
	}		
	if(keyBoard.x){
		camera.RotateX(5.0);
	}		
	if(keyBoard.y){
		camera.RotateX(-5.0);
	}		
	if(keyBoard.c){
		camera.StrafeRight(-0.1);
	}		
	if(keyBoard.v){
		camera.StrafeRight(0.1);
	}		
	if(keyBoard.f){
		camera.MoveUpward(-0.3);
	}
	if(keyBoard.r){
		camera.MoveUpward(0.3);
	}
	if(keyBoard.m){
		camera.RotateZ(-5.0);
	}
	if(keyBoard.n){
		camera.RotateZ(5.0);
	}
}
void idleEvent(int step) {
	

	glutTimerFunc((unsigned int)DELTA_MILI_TIME, idleEvent, step);
	Update();

	glutPostRedisplay();
	
}

void Display(void){

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
		
	camera.Render();

	//Draw the "world":
	glTranslatef(0.0,-0.5,-6.0);

	glScalef(3.0,1.0,3.0);
	
	GLfloat size = 2.0;
	GLint LinesX = 30;
	GLint LinesZ = 30;

	GLfloat halfsize = size / 2.0;
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		glTranslatef(0.0,-halfsize ,0.0);
		DrawNet(size,LinesX,LinesZ);
		glTranslatef(0.0,size,0.0);
		DrawNet(size,LinesX,LinesZ);
	glPopMatrix();
	glColor3f(0.0,0.0,1.0);
	glPushMatrix();
		glTranslatef(-halfsize,0.0,0.0);	
		glRotatef(90.0,0.0,0.0,halfsize);
		DrawNet(size,LinesX,LinesZ);
		glTranslatef(0.0,-size,0.0);
		DrawNet(size,LinesX,LinesZ);
	glPopMatrix();
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
		glTranslatef(0.0,0.0,-halfsize);	
		glRotatef(90.0,halfsize,0.0,0.0);
		DrawNet(size,LinesX,LinesZ);
		glTranslatef(0.0,size,0.0);
		DrawNet(size,LinesX,LinesZ);
	glPopMatrix();


	//finish rendering:
	glFlush();  
	glutSwapBuffers();

}
void kd(unsigned char key, int x, int y){
	keyBoard.KeyDown(key, x,y);
}

void ku(unsigned char key, int x, int y){
	keyBoard.KeyUp(key, x,y);
}


int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,300);
	glutCreateWindow("camera");
	camera.Move( F3dVector(0.0, 0.0, 3.0 ));
	camera.MoveForward( 1.0 );
	glutDisplayFunc(Display);
	glutTimerFunc(0, idleEvent, 0);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(kd);
	glutKeyboardUpFunc(ku);
	glutMainLoop();
	return 0;             
}
