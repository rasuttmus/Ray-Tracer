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
	
	std::cout << "\n\n>>>---A little render message--->\n\n";

	return 0;
}

void calcRays(){

	for(std::vector<Pixel *>::iterator it = camera->pixels.begin(); it != camera->pixels.end(); ++it)
		(*it)->shootingRays((*it)->getNumberOfRays());
}

void createScene() {
	
	// Create room
	Shape *room = new Room(glm::dvec3(0.0,0.0,0.0), 1.0);

	// Set up viewDirection
	//glm::dvec2 viewDir;
	//viewDir.x = (room->walls.at(4)->corners.at(1).x - room->walls.at(4)->corners.at(0).x) / 2;
	//viewDir.y = (room->walls.at(4)->corners.at(1).y - room->walls.at(4)->corners.at(2).y) / 2;

	glm::dvec2 width = glm::dvec2(-0.25, 0.25);
	glm::dvec2 height = glm::dvec2(-0.25, 0.25);

	int imageResolutionX = 1;
	int imageResolutionY = 1;

	// Create camera
	camera = new Camera(glm::dvec3(0.5, 0.5, -2.0), width, height, imageResolutionX, imageResolutionY, 10);

	// Create light source
	glm::dvec3 lightPos(0.5, 0.5, -0.5);
	Light *lightSource = new Light(20.0, lightPos, 1.0/6.0);

	camera->addShape(room);

	Shape *cube = new Cube(glm::dvec3(0.25, 0.25, 0.0), 0.5, false, 1);
	//camera->addShape(cube);
	//cubes.push_back(cube);

	//Create sphere
	Shape *sphere = new Sphere(glm::dvec3(0.5,0.5, -0.25), 0.25, false, 1);
	camera->addShape(sphere);
	//spheres.push_back(sphere);

}