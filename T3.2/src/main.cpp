/*
	Gabriel Simmel Nascimento - 9050232
	Victor Luiz Roquete Forbes - 9293394
	Marcos Cesar Ribeiro de Camargo - 9278045
	José Augusto Noronha de Menezes Neto - 9293049
*/

#include <cmath>
#include <GL/glut.h>

#include "callbacks.hpp"

#define M 1400
#define N 900

int main(int argc, char *argv[]) {
	// Initializing camera and objects.
	myInit();

	// Initializing GLUT and Window.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(M, N);
	g_WindowHandle = glutCreateWindow("T3");

	// Callbacks.
	glutDisplayFunc(Render);
	glutReshapeFunc(changeSize);
	glutTimerFunc(0, Update, 0);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// Enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

