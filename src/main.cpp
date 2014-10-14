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

//using namespace std;

void createScene();
//class Camera;


//Camera *cam;




int main(int argc, char **argv)
{

	createScene();
	//cam = new Camera(3);
	//cam->renderImage();
	std::cout << "\n\n>>>---A little render message--->\n\n";


	return 0;
}

void createScene() {
	Rectangle *wall1 = new Rectangle(glm::vec3(0, 1, -1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1));
	Rectangle *wall2 = new Rectangle(glm::vec3(0, 1, -1), glm::vec3(1, 1, -1), glm::vec3(1, 1, 0), glm::vec3(0, 1, 0));
	Rectangle *wall3 = new Rectangle(glm::vec3(1, 1, 0), glm::vec3(1, 1, -1), glm::vec3(1, 0, -1), glm::vec3(1, 0, 0));
	Rectangle *wall4 = new Rectangle(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, -1), glm::vec3(0, 0, -1));
	Rectangle *wall5 = new Rectangle(glm::vec3(0, 1, 0), glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 0));
	Room *room = new Room(wall1, wall2, wall3, wall4, wall5, glm::vec3(0,0,0), 1.0);
	
	glm::vec2 viewDir;
	viewDir.x = (wall5->corners.at(1).x - wall5->corners.at(0).x) / 2;
	viewDir.y = (wall5->corners.at(1).y - wall5->corners.at(2).y) / 2;

	//Camera *camera = 

	//std::cout << "room: " << room << std::endl;
	//Rectangle *rectange0 = new Rectangle();

	//Cube *cube = new Cube();
}