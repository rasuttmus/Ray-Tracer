#include "sphere.h"


Sphere::Sphere(glm::vec3 p, float r, bool t, float ref): 
position(p), radius(r), transparency(t), refractiveIndex(ref)
{ 
}

glm::vec3 Sphere::calculateIntersections(Ray *r) {
	

	glm::vec3 intersectionPoint = glm::vec3(0.0f, 0.0f, 0.0f); 
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
	}
	else{
		//two intersections
		if( -b + sqrt((b * b) - (4 * c)) > 0){
			float t = (-b + sqrt((b * b) - (4 * c)))/2;
			intersectionPoint.x = startingPoint.x + (normDir.x * t);
			intersectionPoint.y = startingPoint.y + (normDir.y * t);
			intersectionPoint.z = startingPoint.z + (normDir.z * t);
		}
		else{
			float t = (-b - sqrt((b * b) - (4 * c)))/2;
			intersectionPoint.x = startingPoint.x + (normDir.x * t);
			intersectionPoint.y = startingPoint.y + (normDir.y * t);
			intersectionPoint.z = startingPoint.z + (normDir.z * t);
		}

	}
	//std::cout << "(" << intersectionPoint.x <<", " << intersectionPoint.y <<", " << intersectionPoint.z << ")" << std::endl;

	return intersectionPoint;
	
}

void Sphere::calculateChildrenRays(Ray *r) {

	glm::vec3 intersectionAt = calculateIntersections(r);
	
	glm::vec3 intersectionNormal = glm::normalize(intersectionAt - position);

	glm::vec3 inDirection = glm::normalize(r->getDirection());
	glm::vec3 reflectedDirection = -1.0f * (2.0f * (glm::dot(intersectionNormal,inDirection) * intersectionNormal) - inDirection);
	
	r->reflectionRay = new Ray(reflectedDirection, intersectionAt);

	if(transparency == true){
		//Refraction
		float n1 = 1.0f;
		float n2 = refractiveIndex;
		float n = n1/n2;
		float cosI = glm::dot(intersectionNormal, inDirection);
		float sinT2 = 1.0f - n * n * (1.0f - cosI * cosI);

		if(sinT2 >= 0.0f){
			glm::vec3 refractedDirection = n * inDirection - (n * cosI + (float)sqrt(sinT2)) * intersectionNormal;
			
			r->refractionRay = new Ray(refractedDirection, intersectionAt);
		}
	}
}