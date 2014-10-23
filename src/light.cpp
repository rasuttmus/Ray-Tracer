#include "light.h"

Light::Light(double r, glm::dvec3 p, double s): 
radiance(r), position(p), size(s)
{
    glm::dvec3 p0(0.0, 1.0, -1.0);
    glm::dvec3 p1(1.0, 1.0, -1.0);
    glm::dvec3 p2(1.0, 1.0, 0.0);
    glm::dvec3 p3(0.0, 1.0, 0.0);

    lightObject = new Rectangle(p0 * size + position, p1 * size + position, p2 * size + position ,p3 * size + position);
}

glm::dvec3 Light::randomPosition() {
    return glm::dvec3(0.0, 0.0, 0.0);
}