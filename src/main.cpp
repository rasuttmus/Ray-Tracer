//Classes for Ray tracing project in TNCG15
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

//using namespace std;

void createScene();
void calcRays();
//class Camera;


Camera *camera;



int main(int argc, char **argv)
{

	createScene();
	calcRays();
	/*for(std::vector<Pixel *>::iterator pixelIt = pixels.begin(); pixelIt != pixels.end(); ++pixelIt)

		pixelIt->shootingRays(camera->raysPerPixel);

		for(std::vector<Ray *>::iterator rayIt = rays.begin(); rayIt != rays.end(); ++rayIt){
			for(std::vector<Cube *>::iterator cubeIt = cubes.begin(); cubeIt != cubes.end(); ++cubeIt)
				(*cubeIt)->computeChildrenRays((*pixelIt)->(*rayIt));
			}
		}
	}*/

	
	std::cout << "\n\n>>>---A little render message--->\n\n";


	return 0;
}

void calcRays(){

	for(std::vector<Pixel *>::iterator it = camera->pixels.begin(); it != camera->pixels.end(); ++it)
		(*it)->shootingRays((*it)->getNumberOfRays());
/*
    glm::vec3 cubeDist(0.0f, 0.0f, 0.0f);
    glm::vec3 sphereDist(0.0f, 0.0f, 0.0f);

    // Nu du, nu åker vi
	for(std::vector<Pixel *>::iterator pixIt = pixels.begin(); pixIt != pixels.end(); ++pixIt)
	    for(std::vector<Ray *>::iterator rayIt = (*pixIt)->rays.begin(); rayIt != (*pixIt)->rays.end(); ++rayIt){
	        for(std::vector<Cube *>::iterator cubeIt = cubes.begin(); cubeIt != cubes.end(); ++cubeIt){      
	            if(cubeDist >= glm::length((*cubeIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint()))
	            	cubeDist = glm::length((*cubeIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint());
	        }

	        for(std::vector<Sphere *>::iterator sphereIt = spheres.begin(); sphereIt != spheres.end(); ++sphereIt){
	        	if(sphereDist >= glm::length((*sphereIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint()))
	            	sphereDist = glm::length((*sphereIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint());
	        }

	        if(cubeDist >= sphereDist)
	        	(*pixIt)->shootingRays((*pixIt)->getNumberOfRays(), );
	    }
	}*/
}

void createScene() {
	// Create walls to the room
	

	// Create room
	Room *room = new Room(glm::vec3(0,0,0), 1.0);
	
	// Set up viewDirection
	glm::vec2 viewDir;
	viewDir.x = (room->walls.at(4)->corners.at(1).x - room->walls.at(4)->corners.at(0).x) / 2;
	viewDir.y = (room->walls.at(4)->corners.at(1).y - room->walls.at(4)->corners.at(2).y) / 2;

	glm::vec2 width = glm::vec2(-0.25f, 0.25f);
	glm::vec2 height = glm::vec2(-0.25f, 0.25f);

	int imageResolutionX = 4;
	int imageResolutionY = 4;

	// Create camera
	camera = new Camera(-2.0, width, height, imageResolutionX, imageResolutionY, 10);

	// Create light source
	glm::vec3 lightPos(0.5f, 0.5f, -0.5f);
	Light *lightSource = new Light(20.0f, lightPos, 1.0f/6.0f);

	Shape *cube = new Cube(glm::vec3(0.1f, 0.1f, -0.25f), 0.25f, false, 1);
	camera->addShape(cube);
	//cubes.push_back(cube);

	//Create sphere
	Shape *sphere = new Sphere(glm::vec3(0.5f,0.1f,-0.25f), 0.45f, false, 1);
	camera->addShape(sphere);
	//spheres.push_back(sphere);

}