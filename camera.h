#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "../glm/glm.hpp"

class Camera{
public:
    //Instance vairables
    glm::vec3 position;
    glm::vec3 viewDirection;
    float viewPlaneDistance;
    int raysPerPixel;
    //vector<*Pixel> pixels;

    //construtor
    Camera();
    Camera(int p);
    //Instance methods
    void renderImage();
    void mappingFunction();
    void displayImage();


};