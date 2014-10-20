#include "ray.h"

Ray::Ray(glm::vec3 d, glm::vec3 s):
		 direction(d), startingPoint(s)  {
    //std::cout << "direction: " << direction.x << "   " << direction.y << "   " << direction.z << std::endl;
}

glm::vec3 Ray::calculateColor() {
    return glm::vec3(0,0,0);
}

glm::vec3 Ray::calculateLocalContribution() {
    return glm::vec3(0,0,0);
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