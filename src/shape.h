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
    virtual glm::dvec3 calculateIntersections(glm::dvec3, glm::dvec3) = 0;
    virtual void computeChildrenRays(Ray *) = 0;
    virtual int getType() = 0;
    //virtual glm::vec3 getIntersectionNormal() = 0;
};

#endif // SHAPE_H