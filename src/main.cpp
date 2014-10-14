//Classes for Ray tracing project in TNCG15
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "glm/glm.hpp"

#include "camera.h"

using namespace std;
//class Camera;

/*
class Camera{
public:
	//Instance vairables
	glm::vec3 position;
	glm::vec3 viewDirection;
	float viewPlaneDistance;
	int raysPerPixel;
	//vector<*Pixel> pixels;

	//construtor

	//Instance methods
	void renderImage();
	void mappingFunction();
	void displayImage();


};*/
Camera *cam;

class Pixel{
public:
	//Instance variables
	//vector<&Ray> rays;
	glm::vec3 colorOfPixel;
	//constructor

	//Instance methods
	void shootingRays();

};

class Ray{
public:
	//Instance variables
	glm::vec3 startingPoint;
	glm::vec3 direction;
	float importance;
	glm::vec3 color;
	bool finalNode;
	//var *childrenNodes;
	bool insideObject;


	//constructor

	//Instance methods	
	glm::vec3 calculateColor();
	glm::vec3 calculateLocalContribution();

};

class Sphere{
public:
	//Instance variables
	glm::vec3 position;
	float radius;
	bool transparency;	
	float refractiveIndex;

	//contructor

	//Instance methods

};

class Rectangle{};

class Cube{};

class Wall{};

class Light{};



int main(int argc, char **argv)
{

	cam = new Camera(3);
	cam->renderImage();
	cout << "\n\n>>>---A little render message--->\n\n";


	return 0;
}