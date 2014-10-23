#include "glm/glm.hpp"
#include <vector>
#include "rectangle.h"
#include "ray.h"
#include "shape.h"

#ifndef CUBE_H
#define CUBE_H

#define CUBE_SHAPE 0
#define SPHERE_SHAPE 1
#define ROOM_SHAPE 2

class Rectangle;

class Cube: public Shape{
public:
    double size;
    bool transparent;
    double refractiveIndex;
    std::vector<Rectangle *> rectangles;

    //constructors
    Cube(glm::dvec3, double, bool, double = 0.0);

    //methods
    void initRectangleObjects();
    glm::dvec3 calculateIntersections(glm::dvec3, glm::dvec3);
    void computeChildrenRays(Ray *);
    void addRectangle(Rectangle *);

    void setPosition(glm::dvec3);
    glm::dvec3 getPosition();
    int getType();
   // glm::dvec3 getIntersectionNormal();

private:
    glm::dvec3 position;
    glm::dvec3 intersectionNormal;
};

#endif // CUBE_H