#include <iostream>
#include <cmath>
#include "glm/glm.hpp"
#include "debug.h"

#ifndef RAY_H
#define RAY_H

class Ray{
public:

    Ray *reflectionRay = NULL;
    Ray *refractionRay = NULL;

    //constructor
    Ray(glm::dvec3, glm::dvec3);
    
    //Instance methods  
    glm::dvec3 calculateColor(glm::dvec3, int);
    glm::dvec3 calculateLocalContribution(glm::dvec3, int);
    void calculateImportance(double, bool);
    glm::dvec3 calculateShadowRay(glm::dvec3, glm::dvec3);

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

    void setIntersectionPoint(glm::dvec3);
    glm::dvec3 getIntersectionPoint();

    void setIntersectionType(int);
    int getIntersectionType();

    void setIntersectionNormal(glm::dvec3);

private:
    glm::dvec3 startingPoint;
    glm::dvec3 direction;
    bool insideObject;
    bool intersected = false;
    bool finalNode = false;
    double importance;
    glm::dvec3 color = glm::dvec3(0.0, 0.0, 0.0);
    double reflectedRadiance;
    double transmittedRadiance;
    glm::dvec3 intersectionPoint;
    int intersectionType;
    glm::dvec3 intersectionNormal;
};

#endif // RAY_H