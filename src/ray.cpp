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