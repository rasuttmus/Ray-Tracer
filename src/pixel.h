#include "glm/glm.hpp"

#include "ray.h"

class Pixel{
public:
    //Instance variables
    //vector<&Ray> rays;
    glm::vec3 colorOfPixel;

    //constructor
    Pixel();
    //Instance methods
    void shootingRays();

};