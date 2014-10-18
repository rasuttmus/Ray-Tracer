#include <iostream>
#include "glm/glm.hpp"

#ifndef RAY_H
#define RAY_H

class Ray{
public:
    //Instance variables
    glm::vec3 startingPoint;
    glm::vec3 direction;
    float importance;
    glm::vec3 color;
    bool finalNode;
    bool insideObject;
    Ray *reflectionRay;
    Ray *refractionRay;



    //constructor
    Ray(glm::vec3, glm::vec3);
    //Instance methods  
    glm::vec3 calculateColor();
    glm::vec3 calculateLocalContribution();

};

#endif // RAY_H