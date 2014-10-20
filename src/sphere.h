#include "glm/glm.hpp"
#include "ray.h"
#include <cmath>

#ifndef SPHERE_H
#define SPHERE_H

class Sphere{
public:
    //Instance variables
    glm::vec3 position;
    float radius;
    bool transparency;  
    float refractiveIndex;

    //contructor
    Sphere(glm::vec3, float, bool, float);

    //Instance methods
    glm::vec3 calculateIntersections(Ray*);
    void calculateChildrenRays();

};

#endif // SPHERE_H