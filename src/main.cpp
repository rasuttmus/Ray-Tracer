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


void createScene();
void calcRays();

Camera *camera;

int main(int argc, char **argv)
{
	 
    //Timer begin
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::cout << "Creating scene...";
	createScene();
	std::cout << " Done" << std::endl << std::endl << "Rendering...";
	std::cout << " ";
	calcRays();
	camera->renderImage();
	std::cout << "Done" << std::endl << std::endl;
	
	//Timer end
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();

    std::cout << "Duration in seconds:" << duration << std::endl << std::endl << std::endl;
	
	return 0;
}

void calcRays(){

	for(std::vector<Pixel *>::iterator it = camera->pixels.begin(); it != camera->pixels.end(); ++it)
		(*it)->shootingRays();
}

void createScene() {
	
	// Create room
	Shape *room = new Room(glm::dvec3(0.0, 0.0, 0.0), 1.0, glm::dvec3(0.0, 0.0, 1.0), glm::dvec3(0.8, 0.8, 0.8), glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(0.8, 0.8, 0.8), glm::dvec3(1.0, 0.1, 0.1));

	// Set up viewDirection
	//glm::dvec2 viewDir;
	//viewDir.x = (room->walls.at(4)->corners.at(1).x - room->walls.at(4)->corners.at(0).x) / 2;
	//viewDir.y = (room->walls.at(4)->corners.at(1).y - room->walls.at(4)->corners.at(2).y) / 2;

	glm::dvec2 width = glm::dvec2(-0.5, 0.5);
	glm::dvec2 height = glm::dvec2(-0.5, 0.5);

	int imageResolutionX = 512;
	int imageResolutionY = 512;

	// Create camera
	camera = new Camera(glm::dvec3(0.5, 0.5, -2.0), width, height, imageResolutionX, imageResolutionY, 160);

	// Create light source
	Light *lightSource = new Light(20.0, glm::dvec3(0.4, 0.99, -0.4), 0.2);
	camera->addShape(lightSource);

	camera->addShape(room);

	//Create cube
	//Shape *cube1 = new Cube(glm::dvec3(0.1, 0.05, -0.5), 0.2, false, glm::dvec3(0.61, 0.32, 0.75), 1.5);
	//camera->addShape(cube1);

	//Create sphere
	Shape *sphere = new Sphere(glm::dvec3(0.1, 0.75, -0.1), 0.1, false, 1.5, glm::dvec3(0.5, 0.5, 0.5));
	camera->addShape(sphere);

	Shape *sphere2 = new Sphere(glm::dvec3(0.75, 0.4, -0.6), 0.15, true, 1.5, glm::dvec3(0.7, 0.7, 1.0));
	camera->addShape(sphere2);

	Shape *sphere3 = new Sphere(glm::dvec3(0.5, 0.4, -0.3), 0.12, false, 1.5, glm::dvec3(1.0, 1.0, 0.7));
	camera->addShape(sphere3);

}