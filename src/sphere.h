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
    float radius;
    bool transparency;  
    float refractiveIndex;

    //contructor
    Sphere(glm::vec3, float, bool, float);

    //Instance methods
    glm::vec3 calculateIntersections(glm::vec3, glm::vec3);
    void computeChildrenRays(Ray *);
    void setPosition(glm::vec3);
    glm::vec3 getPosition();
    int getType();

private:
    glm::vec3 position;

};

#endif // SPHERE_H