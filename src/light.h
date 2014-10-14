#include "glm/glm.hpp"

class Light{
    public:
    float radiance;
    glm::vec3 position;
    float size;

    //constructor
    Light();

    //methods
    glm::vec3 randomPosition();

};