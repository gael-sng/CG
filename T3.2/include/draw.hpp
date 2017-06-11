#ifndef _DRAW_HPP_
#define _DRAW_HPP_

#include "transform.hpp"

void applyTransform(Transform* obj);
void drawTorus(Transform* torus, bool selected);
void drawCube(Transform* cube, bool selected);
void drawGround();
void drawTeapot(Transform* teapot, bool selected);

#endif