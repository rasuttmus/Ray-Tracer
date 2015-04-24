#include "glm/glm.hpp"
#include <vector>
#include <ctime>

#include "ray.h"
#include "shape.h"
#include "debug.h"

class Pixel{
public:
    //Instance variables
    std::vector<Ray *> rays;
    std::vector<Shape *> shapes;
    std::vector<Ray *> shadowRays;
    double pixelSize;
    int pixelPosX;
    int pixelPosY;
    glm::dvec3 cameraPos;

    //constructor
    Pixel(int, double, int, int, glm::dvec3);
   // ~Pixel();

    //Instance methods
    void shootingRays();
    void shootChildrenRays(Ray *, int);
    void addRay(Ray *);

    int getNumberOfRays();

    void setColorOfPixel(glm::dvec3);
    glm::dvec3 getColorOfPixel();

private:
    int numberOfRays;
    glm::dvec3 colorOfPixel;
};