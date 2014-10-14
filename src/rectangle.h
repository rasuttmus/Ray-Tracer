#include <vector>
#include "glm/glm.hpp"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    std::vector<glm::vec3> corners;

    //constructor
    Rectangle(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
    //methods
    glm::vec3 calculateIntersections();
    void computeChildrenRays();
    void addCorner(glm::vec3);
};

#endif // RECTANGLE_H