#include <vector>
#include <iostream>
#include "glm/glm.hpp"
#include "ray.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

//class Ray;

class Rectangle {
public:
    std::vector<glm::vec3> corners;
    glm::vec3 normal;

    //constructor
    Rectangle(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
    //methods
    glm::vec3 calculateIntersections(Ray *);
    void computeChildrenRays(Ray *, glm::vec3);
    void addCorner(glm::vec3);
    float calcRectangleEquation();
};

#endif // RECTANGLE_H