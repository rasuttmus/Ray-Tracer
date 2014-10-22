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
    

    //constructor
    Rectangle(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
    //methods
    glm::vec3 calculateIntersections(glm::vec3, glm::vec3);
    void computeChildrenRays(Ray *, glm::vec3);
    void addCorner(glm::vec3);
    void calcRectNormal();
    void setNormal(glm::vec3);
    glm::vec3 getNormal();


private:
	glm::vec3 normal;
};

#endif // RECTANGLE_H