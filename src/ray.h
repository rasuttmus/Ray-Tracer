#include <iostream>
#include "glm/glm.hpp"

#ifndef RAY_H
#define RAY_H

class Ray{
public:

    float importance;
    glm::vec3 color;
    bool finalNode;
    Ray *reflectionRay;
    Ray *refractionRay;

    //constructor
    Ray(glm::vec3, glm::vec3);
    
    //Instance methods  
    glm::vec3 calculateColor();
    glm::vec3 calculateLocalContribution();

    void setStartingPoint(glm::vec3);
    glm::vec3 getStartingPoint();

    void setDirection(glm::vec3);
    glm::vec3 getDirection();

    void setInsideObject(bool);
    bool getInsideObject();

    void setIntersected(bool);
    bool getIntersected();

private:
    glm::vec3 startingPoint;
    glm::vec3 direction;
    bool insideObject;
    bool intersected = false;
};

#endif // RAY_H