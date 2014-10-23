#include "glm/glm.hpp"
#include "ray.h"
#include "shape.h"
#include <cmath>

#ifndef SPHERE_H
#define SPHERE_H

#define CUBE_SHAPE 0
#define SPHERE_SHAPE 1

class Sphere: public Shape{

public:
    //Instance variables
    double radius;
    bool transparent;  
    double refractiveIndex;

    //contructor
    Sphere(glm::dvec3, double, bool, double);

    //Instance methods
    glm::dvec3 calculateIntersections(glm::dvec3, glm::dvec3);
    void computeChildrenRays(Ray *);
    void setPosition(glm::dvec3);
    glm::dvec3 getPosition();
    int getType();
    //glm::dvec3 getIntersectionNormal();

private:
    glm::dvec3 position;
   // glm::dvec3 intersectionNormal;

};

#endif // SPHERE_H