//Ray tracer by Rasmus Haapaoja och Tim Brodin
//TNCG015, October 2014

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "glm/glm.hpp"
#include "camera.h"
#include "room.h"
#include "cube.h"
#include "light.h"
#include "sphere.h"
#include "tbb/tbb.h"


void createScene();
void calcRays();

Camera *camera;
float *hej;

int main(int argc, char **argv)
{
     
    //Timer begin
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Rendering.";
    createScene();
    std::cout << ".";
    std::cout << ".";
    calcRays();
    std::cout << "Done" << std::endl << std::endl;
    camera->renderImage();

    //Timer end
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();

    std::cout << "Duration in seconds:" << duration << std::endl << std::endl << std::endl;
    
    return 0;
}

void calcRays(){

    for(std::vector<Pixel *>::iterator it = camera->pixels.begin(); it != camera->pixels.end(); ) {
        (*it)->shootingRays();
        camera->pixelColors.push_back((*it)->getColorOfPixel());
        delete (*it);
        it = camera->pixels.erase(it);
    }
}

void createScene() {
    
    /* CHECK WHY THE ROOF IS GETTING SO DARK */

    // Create room
    Shape *room = new Room(glm::dvec3(0.8, 0.8, 0.8), 1.0, glm::dvec3(0.6, 0.6, 1.0), glm::dvec3(0.8, 0.8, 0.8), glm::dvec3(1.0, 0.6, 0.6), glm::dvec3(0.8, 0.8, 0.8), glm::dvec3(0.8, 0.8, 0.8));

    glm::dvec2 cam_height = glm::dvec2(-0.5, 0.5);
    glm::dvec2 cam_width = glm::dvec2(-0.2824858757, 0.2824858757);


    // 16:9 resolution
    int imageResolutionY = 640;
    int imageResolutionX = 360;

    // 1:1 resolution
    //int imageResolutionX = 512;
    //int imageResolutionY = 512;

    // Create camera
    camera = new Camera(glm::dvec3(0.5, 0.2824858757, -2.0), cam_width, cam_height, imageResolutionX, imageResolutionY, 80);

    // Create light source
    Light *lightSource = new Light(20.0, glm::dvec3(0.4, 0.5549717514, -0.4), 0.2);
    camera->addShape(lightSource);

    camera->addShape(room);

    //Create cube
    //Shape *cube1 = new Cube(glm::dvec3(0.18, 0.17, -0.5), 0.2, false, glm::dvec3(0.6, 0.2, 1.0), 1.5);
    //camera->addShape(cube1);

    //Shape *sphere2 = new Sphere(glm::dvec3(0.4, 0.1, -0.6), 0.1, true, 1.5, glm::dvec3(1.0, 1.0, 1.0));
    //camera->addShape(sphere2);

    //Shape *sphere3 = new Sphere(glm::dvec3(0.3, 0.1, -0.4), 0.1, true, 1.5, glm::dvec3(1.0, 1.0, 1.0));
    //camera->addShape(sphere3);

    //Shape *sphere4 = new Sphere(glm::dvec3(0.5, 0.1, -0.4), 0.1, true, 1.5, glm::dvec3(1.0, 1.0, 1.0));
    //camera->addShape(sphere4);

    //Shape *sphere5 = new Sphere(glm::dvec3(0.7, 0.1, -0.4), 0.1, true, 1.5, glm::dvec3(1.0, 1.0, 1.0));
    //camera->addShape(sphere5);

    Shape *sphere6 = new Sphere(glm::dvec3(0.7, 0.2, -0.5), 0.1, true, 1.5, glm::dvec3(1.0, 1.0, 1.0));
    camera->addShape(sphere6);

    Shape *sphere7 = new Sphere(glm::dvec3(0.3, 0.3, -0.4), 0.07, false, 1.5, glm::dvec3(1.0, 1.0, 1.0));
    camera->addShape(sphere7);

}