#include "sphere.h"


Sphere::Sphere(glm::vec3 p, float r, bool t, float ref): 
position(p), radius(r), transparency(t), refractiveIndex(ref)
{ 
}

glm::vec3 Sphere::calculateIntersections(Ray *r) {
	

	glm::vec3 intersectionPoint = glm::vec3(10000.0f, 10000.0f, 10000.0f); 
	glm::vec3 normDir = glm::normalize(r->getDirection());
    glm::vec3 startingPoint = r->getStartingPoint();

	float b = 2 * (normDir.x * (startingPoint.x - position.x) + normDir.y * (startingPoint.y - position.y) + normDir.z * (startingPoint.z - position.z));
	float c = pow((startingPoint.x - position.x),2) + pow((startingPoint.y - position.y),2) + pow((startingPoint.z - position.z),2) - pow(radius,2);
	float t = 0.0;

	if((b * b) - (4 * c) < 0.0){
		//no intersections
	}
	else if((b * b) - (4 * c) == 0.0){
		//one tangential intersection
		intersectionPoint.x = startingPoint.x + (normDir.x * (-b/2));
		intersectionPoint.y = startingPoint.y + (normDir.y * (-b/2));
		intersectionPoint.z = startingPoint.z + (normDir.z * (-b/2));
        r->setIntersected(true);
	}
	else{
		//two intersections
		if( -b + sqrt((b * b) - (4 * c)) > 0){
			float t = (-b + sqrt((b * b) - (4 * c)))/2;
			intersectionPoint.x = startingPoint.x + (normDir.x * t);
			intersectionPoint.y = startingPoint.y + (normDir.y * t);
			intersectionPoint.z = startingPoint.z + (normDir.z * t);
            r->setIntersected(true);
		}
		else{
			float t = (-b - sqrt((b * b) - (4 * c)))/2;
			intersectionPoint.x = startingPoint.x + (normDir.x * (t/2));
			intersectionPoint.y = startingPoint.y + (normDir.y * (t/2));
			intersectionPoint.z = startingPoint.z + (normDir.z * (t/2));
            r->setIntersected(true);
		}

	}
	//std::cout << "(" << intersectionPoint.x <<", " << intersectionPoint.y <<", " << intersectionPoint.z << ")" << std::endl;

	return intersectionPoint;
	
}

void Sphere::computeChildrenRays(Ray *ray, glm::vec3 intersection) {

}

void Sphere::setPosition(glm::vec3 p){
    position = p;
}

glm::vec3 Sphere::getPosition(){
    return position;
}

int Sphere::getType(){
    return SPHERE_SHAPE;
}