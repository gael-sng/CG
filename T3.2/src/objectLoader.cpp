#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "vector3.hpp"
#include <fstream>
#include <string>

GLuint elephant;

using namespace std;

void loadObj(char *fname){

	FILE *fp;
	vector <Vector3> vertices;
	// vector <Vector3> faces;
	GLfloat x, y, z;
	char ch;
	int one, two, three, four;
	
	elephant = glGenLists(1);
	
	// Abrindo o arquivo.
	// ifstream infile(fname);
	fp = fopen(fname, "r");
	if (!fp){
		printf("can't open file %s\n", fname);
		exit(1);
	}
	

	glPointSize(2.0);

	glNewList(elephant, GL_COMPILE);	
	glPushMatrix();
	vertices.push_back(new Vector3());

	while(!(feof(fp))){
	// string line;
	// while(getline(infile, line)){
	// 	if(line.find('s') == string::npos or line.find('f') == string::npos){

	// 	} else {
	// 	cout << line << endl;
			
	// 	}
		if(fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z) == 4){
			if(ch == 'v'){
				vertices.push_back(new Vector3(x,y,z));
			} else if(ch == 'f'){
				one = (int)x;
				two = (int)y;
				three = (int)z;
				fscanf(fp, " %d", &four);
				cout << ch << " " << x  << " "  << y  << " "  << z << " " << four << endl;
				// separar em draw
				glBegin(GL_POLYGON);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3d(vertices[one].x, vertices[one].y, vertices[one].z);
				glVertex3d(vertices[two].x, vertices[two].y, vertices[two].z);
				glVertex3d(vertices[three].x, vertices[three].y, vertices[three].z);
				// glVertex3d(vertices[four].x, vertices[four].y, vertices[four].z);
				glEnd();
			} else {
				cout << ch << endl;
			}
		}
	}

	glPopMatrix();
	glEndList();
	fclose(fp);
}

//.obj loader code ends here

void reshape(int w,int h){    
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

float elephantrot = 0;
void drawCar(){

	glPushMatrix();
	
	glTranslatef(0, -40.00, -105);
	glColor3f(1.0, 0.23, 0.27);
	glScalef(5, 5, 5);
	glRotatef(elephantrot, 0,1,0);
	
	glCallList(elephant);
	
	glPopMatrix();
	
	elephantrot += 0.6;
	if(elephantrot > 360) elephantrot = elephantrot - 360;
}

void display(void){  
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawCar();
	glutSwapBuffers(); //swap the buffers
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("ObjLoader");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	
	loadObj((char*)"data/SC Fighter VX4 .obj");
	
	glutMainLoop();
	return 0;
}
