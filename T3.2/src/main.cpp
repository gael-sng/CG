/* Main source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Augusto Monteiro 			-	9293095

*/

#include <math.h>
#include <GL/glut.h>

#include "callbacks.hpp"

int main(int argc, char *argv[]) {

	// Initializa my things 
	myInit();

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1400, 900);
	g_WindowHandle = glutCreateWindow("T3");

	// register callbacks
	glutDisplayFunc(Render);
	glutReshapeFunc(changeSize);
	glutTimerFunc(0,Update,0);
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

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

