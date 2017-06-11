/*
	Gabriel Simmel Nascimento - 9050232
	Victor Luiz Roquete Forbes - 9293394
	Marcos Cesar Ribeiro de Camargo - 9278045
	José Augusto Noronha de Menezes Neto - 9293049
*/

#pragma once

extern int g_WindowHandle;

void myInit();
void myCleanup();
bool setSpeed(float);
void Update(int);
void Render();
void changeSize(int, int);
void keyboardUp(unsigned char, int, int);
void keyboardDown(unsigned char, int, int);
void specialUp(int, int, int);
void specialDown(int, int, int);