#include <vector>
#include <iostream>
#include "glm/glm.hpp"
#include "ray.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

//class Ray;

class Rectangle {
public:
    std::vector<glm::dvec3> corners;
    

    //constructor
    Rectangle(glm::dvec3, glm::dvec3, glm::dvec3, glm::dvec3);
    //methods
    glm::dvec3 calculateIntersections(glm::dvec3, glm::dvec3, double);
    void computeChildrenRays(Ray *, glm::dvec3);
    void addCorner(glm::dvec3);
    void calcRectNormal();

    void setNormal(glm::dvec3);
    glm::dvec3 getNormal();

    void setColor(glm::dvec3);
    glm::dvec3 getColor();

private:
	glm::dvec3 normal;
    glm::dvec3 color;
};

#endif // RECTANGLE_H