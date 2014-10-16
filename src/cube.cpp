#include "cube.h"

Cube::Cube(Rectangle *r0, Rectangle *r1, Rectangle *r2, Rectangle *r3, Rectangle *r4, Rectangle *r5, glm::vec3 p, float s, bool t, float ref): 
position(p), size(s), transparent(t), refractiveIndex(ref)
{
    addRectangle(r0);
    addRectangle(r1);
    addRectangle(r2);
    addRectangle(r3);
    addRectangle(r4);
    addRectangle(r5);
}

void Cube::initRectangleObjects(){

}

void Cube::computeChildrenRays(){

}

void Cube::addRectangle(Rectangle *r) {
    rectangles.push_back(r);
}