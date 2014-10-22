#include "glm/glm.hpp"
#include <vector>
#include <ctime>

#include "ray.h"
#include "shape.h"
//#include "camera.h"

class Pixel{
public:
    //Instance variables
    std::vector<Ray *> rays;
    std::vector<Shape *> shapes;
    //std::vector<Sphere *> spheres;
    glm::vec3 colorOfPixel;
    float pixelSize;
    int pixelPosX;
    int pixelPosY;
    glm::vec3 cameraPos;

    //constructor
    Pixel(int, float, int, int, glm::vec3);
    //Instance methods
    void shootingRays(int);
    void addRay(Ray *);

    int getNumberOfRays();

private:
    int numberOfRays;
};