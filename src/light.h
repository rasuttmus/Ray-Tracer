#include "glm/glm.hpp"
#include <stdlib.h>
#include <iostream>
#include "rectangle.h"
#include "shape.h"

#define LIGHT_SHAPE 3

class Light: public Shape{
    public:
    double radiance;
    glm::dvec3 position;
    double size;
    Rectangle *lightObject;

    //constructor
    Light(double, glm::dvec3, double);

    //methods
    glm::dvec3 randomPosition();

    glm::dvec3 calculateIntersections(Ray *);
    void computeChildrenRays(Ray *);
    int getType();
    glm::dvec3 getColor(int);
    int getWallIntersectionIndex();
    double getRefractiveIndex();
    glm::dvec3 getIntersectionNormal();
    bool getTransparency();

};