#pragma once

extern int g_WindowHandle;

void myInit();
void myCleanup();
bool setSpeed(float speed);
void Update(int step);
void Render(void);
void changeSize(int w, int h);
void keyboardUp(unsigned char key, int x, int y);
void keyboardDown(unsigned char key, int x, int y);
void specialUp(int key, int x, int y);
void specialDown(int key, int x, int y);
