/*
	Gabriel Simmel Nascimento - 9050232
	Victor Luiz Roquete Forbes - 9293394
	Marcos Cesar Ribeiro de Camargo - 9278045
	José Augusto Noronha de Menezes Neto - 9293049
*/

#include <math.h>
#include <GL/glut.h>

#include "draw.hpp"

#include "bibutil.h"
#include <stdio.h>
#include <stdlib.h>

#define HIGHLIGHTED 0.2f, 0.3f, 0.6f
#define NOT_HIGHLIGHTED 0.2f, 0.2f, 0.2f

GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;


// Color
GLfloat color[] = {0.0f, 0.0f, 0.0f, 1.0f};

void applyTransform(Transform *obj){
	glTranslatef(obj->position->x, obj->position->y + 0.7, obj->position->z);
	glScalef(obj->scale->x + 1.0, obj->scale->y + 1.0, obj->scale->z + 1.0);

	glRotatef(obj->rotation->x, 1.0f, 0.0f, 0.0f);
	glRotatef(obj->rotation->y, 0.0f, 1.0f, 0.0f);
	glRotatef(obj->rotation->z, 0.0f, 0.0f, 1.0f);
}

void drawTorus(Transform *torus, bool selected){
	applyTransform(torus);

	glNormal3d(0, 1, 0);
	color[0] = 1.0;
	color[1] = 1.2;
	color[2] = 1.3;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	glRotatef(90.0, 1.0, 0.0, 0.0);

	selected ? glColor3f(HIGHLIGHTED) : glColor3f(NOT_HIGHLIGHTED);
	glutSolidTorus(0.4, 0.7, 20.0, 20.0);
}

void drawCube(Transform *cube, bool selected){
	applyTransform(cube);

	glNormal3d(0, 1, 0);
	color[0] = 1.0;
	color[1] = 1.2;
	color[2] = 1.3;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	selected ? glColor3f(HIGHLIGHTED) : glColor3f(NOT_HIGHLIGHTED);
	glutSolidCube(1.5);
}

void drawSky(){
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTeapot(70.0);
}

void drawGround(double height){
	glBegin(GL_QUADS);

	glColor3f(255.0, 255.0, 255.0);
	glVertex3f(-30.0, height, -30.0);

	glColor3f(255.0, 0.0, 255.0);
	glVertex3f(-30.0, height, 30.0);

	glColor3f(255.0, 255.0, 0.0);
	glVertex3f( 30.0, height, 30.0);

	glColor3f(0.0, 255.0, 255.0);
	glVertex3f(30.0, height, -30.0);

	glEnd();

	drawSky();
}

void drawTeapot(Transform *teapot, bool selected){
	glPushMatrix();

	// Apllies transformations
	applyTransform(teapot);

	// Draws obj
	selected? glColor3f(HIGHLIGHTED): glColor3f(NOT_HIGHLIGHTED);
	glutSolidTeapot(0.7f);

	glPopMatrix();
}



// ------------------------------ objeto -------------------

// Apontador para objeto
OBJ *objeto;

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void){

	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de tonalização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle = 55;

	// Inicializa as variáveis usadas para alterar a posição do
	// observador virtual
	obsX = obsY = 0;
	obsZ = 500;

	// Lê o nome do arquivo e chama a rotina de leitura
	//printf("Digite o nome do arquivo que contem o modelo 3D: ");
	//gets(nomeArquivo);

	// Carrega o objeto 3D
	objeto = CarregaObjeto("data/aviao.obj", true);
    printf("Objeto carregado!");

	// E calcula o vetor normal em cada face
	/*if(objeto->normais)
	{
		// Se já existirem normais no arquivo, apaga elas
		free(objeto->normais);
		objeto->normais_por_vertice = false;
	}
	CalculaNormaisPorFace(objeto);*/
}

void DefineIluminacao (void){
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={1.0,1.0,1.0,1.0};	   	// "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};	// "brilho"
	GLfloat posicaoLuz[4]={0.0, 10.0, 100.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;
	

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}


void drawAirplane(Transform *airplane, bool selected){
	glPushMatrix();

	// Apllies transformations
	applyTransform(airplane);

	// Draws obj
	selected? glColor3f(HIGHLIGHTED): glColor3f(NOT_HIGHLIGHTED);
	DesenhaObjeto(objeto);

	glPopMatrix();
}
