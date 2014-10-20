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
//class Camera;


//Camera *cam;




int main(int argc, char **argv)
{

	createScene();
	//Camera *cam = new Camera(3);
	//cam->renderImage();
	std::cout << "\n\n>>>---A little render message--->\n\n";


	return 0;
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

	int imageResolutionX = 2;
	int imageResolutionY = 2;

	// Create camera
	Camera *camera = new Camera(-2.0, width, height, imageResolutionX, imageResolutionY, 10);

	// Create light source
	glm::vec3 lightPos(0.5f, 0.5f, -0.5f);
	Light *lightSource = new Light(20.0f, lightPos, 1.0f/6.0f);

	Cube *cube = new Cube(glm::vec3(0.5f, 0.5f, 0.5f), 0.25f, false);



	//Create sphere
	Sphere *sphere = new Sphere(glm::vec3(0.5f,0.5f,-0.5f), 0.25f, false, 1);


	//std::cout << "room: " << room << std::endl;
	//Rectangle *rectange0 = new Rectangle();

	//Cube *cube = new Cube();
}