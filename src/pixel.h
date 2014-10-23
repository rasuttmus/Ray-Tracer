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
    glm::dvec3 colorOfPixel;
    double pixelSize;
    int pixelPosX;
    int pixelPosY;
    glm::dvec3 cameraPos;

    //constructor
    Pixel(int, double, int, int, glm::dvec3);
    //Instance methods
    void shootingRays(int);
    void shootChildrenRays(Ray *, int);
    void addRay(Ray *);

    int getNumberOfRays();

private:
    int numberOfRays;
};