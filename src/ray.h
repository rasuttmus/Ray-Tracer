#include <iostream>
#include "glm/glm.hpp"

#ifndef RAY_H
#define RAY_H

class Ray{
public:

    Ray *reflectionRay;
    Ray *refractionRay;

    //constructor
    Ray(glm::dvec3, glm::dvec3);
    
    //Instance methods  
    void calculateColor();
    glm::dvec3 calculateLocalContribution();

    void setStartingPoint(glm::dvec3);
    glm::dvec3 getStartingPoint();

    void setDirection(glm::dvec3);
    glm::dvec3 getDirection();

    void setInsideObject(bool);
    bool getInsideObject();

    void setIntersected(bool);
    bool getIntersected();

    void setFinalNode(bool);
    bool getFinalNode();

    void setImportance(double);
    double getImportance();

    void setColor(glm::dvec3);
    glm::dvec3 getColor();

private:
    glm::dvec3 startingPoint;
    glm::dvec3 direction;
    bool insideObject;
    bool intersected = false;
    bool finalNode = false;
    double importance;
    glm::dvec3 color;
};

#endif // RAY_H