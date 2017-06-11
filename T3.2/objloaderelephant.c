//header

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

//globals

GLuint elephant;
float elephantrot;
char ch='1';

//struct Vertex
typedef struct vertex{
  GLfloat x;
  GLfloat y;
  GLfloat z;
}Vertex;


//other functions and main


//allocates struct vertex
Vertex* alocaVertex(){
  int i;
  Vertex* vertex = (Vertex*)malloc(sizeof(Vertex)*(100000));
  for(i = 0; i < 100000; i++){
    vertex[i].x = 0;
    vertex[i].y = 0;
    vertex[i].z = 0;
  }
  return vertex;
}

//.obj loader code begins

void loadObj(char *fname){
  FILE *fp;
  Vertex *vertex = alocaVertex();
  int read;
  GLfloat x, y, z;
  char ch;
  int i;
  int one, two, three;
  elephant=glGenLists(1);
  fp=fopen(fname,"r");
  if (!fp){
    printf("can't open file %s\n", fname);
	  exit(1);
  }
  glPointSize(2.0);
  glNewList(elephant, GL_COMPILE);
  {
    glPushMatrix();
    //glBegin(GL_POINTS);
      i = 0;
      while(!(feof(fp))){
        read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
        if(read == 4 && ch == 'v'){
          vertex[i].x = x;
          vertex[i].y = y;
          vertex[i].z = z;
          i++;
        }
        if(read == 4 && ch == 'f'){
          one = (int)x;
          two = (int)y;
          three = (int)z;
          glBegin(GL_POLYGON);
          glColor3f(1.0f, 0.0f, 0.0f);
          glVertex3d(vertex[one - 1].x, vertex[one - 1].y, vertex[one - 1].z);
          glVertex3d(vertex[two - 1].x, vertex[two - 1].y, vertex[two - 1].z);
          glVertex3d(vertex[three - 1].x, vertex[three - 1].y, vertex[three - 1].z);
          glEnd();
        }
      }
    //glEnd();
  }
  glPopMatrix();
  glEndList();
  fclose(fp);
}

//.obj loader code ends here

void reshape(int w,int h){    
  glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	//glOrtho(-25,25,-2,2,0.1,100);	
	glMatrixMode(GL_MODELVIEW);
}

void drawCar(){
 	glPushMatrix();
 	glTranslatef(0,-40.00,-105);
 	glColor3f(1.0,0.23,0.27);
 	glScalef(0.1,0.1,0.1);
 	glRotatef(elephantrot,0,1,0);
 	glCallList(elephant);
 	glPopMatrix();
 	elephantrot=elephantrot+0.6;
 	if(elephantrot>360)elephantrot=elephantrot-360;
}

void display(void){  
  glClearColor (0.0,0.0,0.0,1.0); 
 	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glLoadIdentity();
 	drawCar();
 	glutSwapBuffers(); //swap the buffers
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,450);
	glutInitWindowPosition(20,20);
	glutCreateWindow("ObjLoader");
	glutReshapeFunc(reshape);
  glutDisplayFunc(display);
	glutIdleFunc(display);
  loadObj("data/teapot.obj");//replace porsche.obj with radar.obj or any other .obj to display it
	glutMainLoop();
	return 0;
}
