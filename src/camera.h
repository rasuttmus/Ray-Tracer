#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "glm/glm.hpp"
#include "pixel.h"

class Pixel;

class Camera{
public:
    //Instance vairables
    glm::dvec3 position;
    glm::dvec3 viewDirection;
    double viewPlaneDistance;
    glm::dvec2 viewPlaneResolution;
    int raysPerPixel;
    std::vector<Pixel*> pixels;

    //construtor
    Camera(glm::dvec3, glm::dvec2, glm::dvec2, int, int, int);
    //Instance methods
    void renderImage();
    void mappingFunction();
    void displayImage();
    void createPixels(int imgResX, int imgResY);
    void addShape(Shape *);
    double getRaysPerPixel();
};