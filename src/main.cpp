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

	createScene();
	calcRays();
	camera->renderImage();
	std::cout << "\n\n>>>---A little render message--->\n\n";

	return 0;
}

void calcRays(){

	for(std::vector<Pixel *>::iterator it = camera->pixels.begin(); it != camera->pixels.end(); ++it)
		(*it)->shootingRays((*it)->getNumberOfRays());
}

void createScene() {
	
	// Create room
	Shape *room = new Room(glm::dvec3(0.0, 0.0, 0.0), 1.0, glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.8, 0.8, 0.8), glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(0.8, 0.8, 0.8), glm::dvec3(1.0, 0.1, 0.1));

	// Set up viewDirection
	//glm::dvec2 viewDir;
	//viewDir.x = (room->walls.at(4)->corners.at(1).x - room->walls.at(4)->corners.at(0).x) / 2;
	//viewDir.y = (room->walls.at(4)->corners.at(1).y - room->walls.at(4)->corners.at(2).y) / 2;

	glm::dvec2 width = glm::dvec2(-0.5, 0.5);
	glm::dvec2 height = glm::dvec2(-0.5, 0.5);

	int imageResolutionX = 256;
	int imageResolutionY = 256;

	// Create camera
	camera = new Camera(glm::dvec3(0.5, 0.5, -2.0), width, height, imageResolutionX, imageResolutionY, 10);

	// Create light source
	Light *lightSource = new Light(20.0, glm::dvec3(0.4, 0.9999, -0.4), 0.2);
	camera->addShape(lightSource);

	camera->addShape(room);

	//Create cube
	Shape *cube1 = new Cube(glm::dvec3(0.2, 0.1, 0.1), 0.3, false, glm::dvec3(0.0, 0.4, 0.8), 1.5);
	//camera->addShape(cube1);

	//Create sphere
	Shape *sphere = new Sphere(glm::dvec3(0.7, 0.4, -0.2), 0.20, true, 1.5, glm::dvec3(0.5, 0.5, 1.0));
	camera->addShape(sphere);

	Shape *sphere2 = new Sphere(glm::dvec3(0.35, 0.5, -0.15), 0.10, false, 1.2, glm::dvec3(0.5, 1.0, 0.5));
	camera->addShape(sphere2);

	Shape *sphere3 = new Sphere(glm::dvec3(0.2, 0.45, -0.2), 0.12, false, 1.5, glm::dvec3(0.3, 0.6, 0.4));
	//camera->addShape(sphere3);

}