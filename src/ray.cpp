#include "ray.h"

Ray::Ray(glm::vec3 d): direction(d) {
    std::cout << "direction: " << direction.x << "   " << direction.y << "   " << direction.z << std::endl;
}

glm::vec3 Ray::calculateColor() {
    return glm::vec3(0,0,0);
}

glm::vec3 Ray::calculateLocalContribution() {
    return glm::vec3(0,0,0);
}

glm::vec4 Ray::calcRayEquation() {
/*
    glm::vec3 A = startingPoint;
    glm::vec3 B = direction;

    glm::vec3 AB = B - A;

    glm::vec3 EQ(startingPoint.x + );
    

*/

    return glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void Ray::setStartingPoint(glm::vec3 s) {
    startingPoint = s;
}

glm::vec3 Ray::getStartingPoint() {
    return startingPoint;
}

void Ray::setDirection(glm::vec3 d) {
    direction = d;
}

glm::vec3 Ray::getDirection() {
    return direction;
}

void Ray::setInsideObject(bool i) {
    insideObject = i;
}

bool Ray::getInsideObject() {
    return insideObject;
}