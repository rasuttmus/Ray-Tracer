#include "light.h"

Light::Light(double r, glm::dvec3 p, double s): 
radiance(r), position(p), size(s)
{
    glm::dvec3 p0(0.0, 1.0, -1.0);
    glm::dvec3 p1(1.0, 1.0, -1.0);
    glm::dvec3 p2(1.0, 1.0, 0.0);
    glm::dvec3 p3(0.0, 1.0, 0.0);

    lightObject = new Rectangle(p0 * size + position, p1 * size + position, p2 * size + position ,p3 * size + position);
    randomPosition();
}

glm::dvec3 Light::randomPosition() {

    glm::dvec3 randPos(0.0, 0.0, 0.0);
    srand(static_cast <double> (time(0)));

    randPos.x = lightObject->corners.at(0).x + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / ((lightObject->corners.at(1).x) - lightObject->corners.at(0).x)));
    randPos.y = 1.0;
    randPos.z = lightObject->corners.at(2).z + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / ((lightObject->corners.at(1).z) - lightObject->corners.at(2).z)));

    std::cout << "random pos on light source: (" << randPos.x << ", " << randPos.y << ", " << randPos.z << ")" << std::endl;

    return randPos;
}