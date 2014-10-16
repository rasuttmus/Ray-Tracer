#include "glm/glm.hpp"
#include <stdlib.h>
#include <iostream>
#include "rectangle.h"

class Light{
    public:
    float radiance;
    glm::vec3 position;
    float size;
    Rectangle *lightObject;

    //constructor
    Light(float, glm::vec3, float);

    //methods
    glm::vec3 randomPosition();

};