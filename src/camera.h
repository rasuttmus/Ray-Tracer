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
    glm::vec3 position;
    glm::vec3 viewDirection;
    float viewPlaneDistance;
    glm::vec2 viewPlaneResolution;
    int raysPerPixel;
    std::vector<Pixel*> pixels;

    //construtor
    Camera(float, glm::vec2, glm::vec2, int, int, int);
    //Instance methods
    void renderImage();
    void mappingFunction();
    void displayImage();
    void createPixels(int imgResX, int imgResY);
    void addShape(Shape *);
};