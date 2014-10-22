#include "light.h"

Light::Light(float r, glm::vec3 p, float s): 
radiance(r), position(p), size(s)
{
    glm::vec3 p0(0.0f, 1.0f, -1.0f);
    glm::vec3 p1(1.0f, 1.0f, -1.0f);
    glm::vec3 p2(1.0f, 1.0f, 0.0f);
    glm::vec3 p3(0.0f, 1.0f, 0.0f);

    lightObject = new Rectangle(p0 * size + position, p1 * size + position, p2 * size + position ,p3 * size + position);
}

glm::vec3 Light::randomPosition() {
    return glm::vec3(0,0,0);
}