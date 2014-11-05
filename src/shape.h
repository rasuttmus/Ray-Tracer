#ifndef SHAPE_H
#define SHAPE_H
#include "glm/glm.hpp"
/**
* Shape abstraction class.
* This is an abstract class for the shapes it contains
* all that is required in a shape.
*/

class Shape {
public:
    virtual glm::dvec3 calculateIntersections(Ray *r) = 0;
    virtual void computeChildrenRays(Ray *) = 0;
    virtual int getType() = 0;
    virtual glm::dvec3 getColor(int) = 0;
    virtual int getWallIntersectionIndex() = 0;
    virtual glm::dvec3 randomPosition() = 0;
    virtual double getRefractiveIndex() = 0;
    virtual glm::dvec3 getIntersectionNormal() = 0;
    virtual bool getTransparency() = 0;
};

#endif // SHAPE_H