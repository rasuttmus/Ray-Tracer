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

    //contructor
    Sphere(glm::dvec3, double, bool, double, glm::dvec3);

    //Instance methods
    glm::dvec3 calculateIntersections(Ray *);
    void computeChildrenRays(Ray *);
    void setPosition(glm::dvec3);
    glm::dvec3 getPosition();
    int getType();

    void setColor(glm::dvec3);
    glm::dvec3 getColor(int);

    int getWallIntersectionIndex();

    glm::dvec3 randomPosition();

    double getRefractiveIndex();
    
    glm::dvec3 getIntersectionNormal();

    bool getTransparency();

private:
    glm::dvec3 position;
    glm::dvec3 color;
    double refractiveIndex;
    glm::dvec3 intersectionNormal;
    bool transparent;

};

#endif // SPHERE_H