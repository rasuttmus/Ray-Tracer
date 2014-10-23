#include "glm/glm.hpp"
#include <stdlib.h>
#include <iostream>
#include "rectangle.h"

class Light{
    public:
    double radiance;
    glm::dvec3 position;
    double size;
    Rectangle *lightObject;

    //constructor
    Light(double, glm::dvec3, double);

    //methods
    glm::dvec3 randomPosition();

};