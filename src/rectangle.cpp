#include "rectangle.h"

Rectangle::Rectangle(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) {
    addCorner(c0);
    addCorner(c1);
    addCorner(c2);
    addCorner(c3);
}

glm::vec3 Rectangle::calculateIntersections() {
    return glm::vec3(0,0,0);
}

void Rectangle::computeChildrenRays() {

}

void Rectangle::addCorner(glm::vec3 c) {
    corners.push_back(c);
}