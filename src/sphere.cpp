#include "sphere.h"


Sphere::Sphere(glm::vec3 p, float r, bool t, float ref): 
position(p), radius(r), transparency(t), refractiveIndex(ref)
{ 
}

glm::vec3 Sphere::calculateIntersections(Ray *r) {
	

	glm::vec3 intersectionPoint = glm::vec3(0.0f, 0.0f, 0.0f); 
	glm::vec3 normDir = glm::normalize(r->direction);

	float b = 2 * (normDir.x * (r->startingPoint.x - position.x) + normDir.y * (r->startingPoint.y - position.y) + normDir.z * (r->startingPoint.z - position.z));
	float c = pow((r->startingPoint.x - position.x),2) + pow((r->startingPoint.y - position.y),2) + pow((r->startingPoint.z - position.z),2) - pow(radius,2);
	float t = 0.0;

	if((b * b) - (4 * c) < 0.0){
		//no intersections
	}
	else if((b * b) - (4 * c) == 0.0){
		//one tangential intersection
		intersectionPoint.x = r->startingPoint.x + (normDir.x * (-b/2));
		intersectionPoint.y = r->startingPoint.y + (normDir.y * (-b/2));
		intersectionPoint.z = r->startingPoint.z + (normDir.z * (-b/2));
	}
	else{
		//two intersections
		if( -b + sqrt((b * b) - (4 * c)) > 0){
			float t = (-b + sqrt((b * b) - (4 * c)))/2;
			intersectionPoint.x = r->startingPoint.x + (normDir.x * t);
			intersectionPoint.y = r->startingPoint.y + (normDir.y * t);
			intersectionPoint.z = r->startingPoint.z + (normDir.z * t);
		}
		else{
			float t = (-b - sqrt((b * b) - (4 * c)))/2;
			intersectionPoint.x = r->startingPoint.x + (normDir.x * (t/2));
			intersectionPoint.y = r->startingPoint.y + (normDir.y * (t/2));
			intersectionPoint.z = r->startingPoint.z + (normDir.z * (t/2));
		}

	}
	std::cout << "(" << intersectionPoint.x <<", " << intersectionPoint.y <<", " << intersectionPoint.z << ")" << std::endl;

	return intersectionPoint;
	
}

void Sphere::calculateChildrenRays() {

}