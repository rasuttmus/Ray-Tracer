#include "glm/glm.hpp"
#include <vector>
#include <ctime>

#include "ray.h"

class Pixel{
public:
    //Instance variables
    std::vector<Ray *> rays;
    glm::vec3 colorOfPixel;
    float pixelSize;
    int pixelPosX;
    int pixelPosY;
    glm::vec3 cameraPos;

    //constructor
    Pixel(int, float, int, int, glm::vec3);
    //Instance methods
    void shootingRays(int);
};