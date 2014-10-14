#include <stdlib.h>
#include <stdio.h>
//#include <cmath>
//#include <fstream>
#include <vector>
#include <iostream>
//#include <cassert>
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
    //Camera();
    Camera(float, glm::vec2, glm::vec2, int);
    //Instance methods
    void renderImage();
    void mappingFunction();
    void displayImage();


};