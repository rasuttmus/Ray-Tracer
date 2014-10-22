#include "sphere.h"


Sphere::Sphere(glm::vec3 p, float r, bool t, float ref): 
position(p), radius(r), transparent(t), refractiveIndex(ref)
{ 
	Ray *roy = new Ray(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.5f, 0.5f, 10.2f));
	calculateChildrenRays(roy);

}

glm::vec3 Sphere::calculateIntersections(glm::vec3 startingPoint, glm::vec3 direction) {
	
	glm::vec3 intersectionPoint = glm::vec3(0.0f, 0.0f, 0.0f); 

	float b = 2 * (direction.x * (startingPoint.x - position.x) + direction.y * (startingPoint.y - position.y) + direction.z * (startingPoint.z - position.z));
	float c = pow((startingPoint.x - position.x),2) + pow((startingPoint.y - position.y),2) + pow((startingPoint.z - position.z),2) - pow(radius,2);
	float t = 0.0;

	if((b * b) - (4 * c) < 0.0){
		//no intersections
	}
	else if((b * b) - (4 * c) == 0.0){
		//one tangential intersection
		intersectionPoint.x = startingPoint.x + (direction.x * (-b/2));
		intersectionPoint.y = startingPoint.y + (direction.y * (-b/2));
		intersectionPoint.z = startingPoint.z + (direction.z * (-b/2));
	}
	else{
		//two intersections
		if( -b + sqrt((b * b) - (4 * c)) < 0){
			float t = (-b + sqrt((b * b) - (4 * c)))/2;
			intersectionPoint.x = startingPoint.x + (direction.x * t);
			intersectionPoint.y = startingPoint.y + (direction.y * t);
			intersectionPoint.z = startingPoint.z + (direction.z * t);
		}
		else{
			float t = (-b - sqrt((b * b) - (4 * c)))/2;
			intersectionPoint.x = startingPoint.x + (direction.x * t);
			intersectionPoint.y = startingPoint.y + (direction.y * t);
			intersectionPoint.z = startingPoint.z + (direction.z * t);
		}

	}

	return intersectionPoint;
	
}

void Sphere::calculateChildrenRays(Ray *r) {

	glm::vec3 inDirection = glm::normalize(r->getDirection());
	glm::vec3 parentPos = r->getStartingPoint();
	glm::vec3 refractedDirection = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 intersectionAt = calculateIntersections(parentPos, inDirection);
	
	glm::vec3 intersectionNormal = glm::normalize(intersectionAt - position);
	glm::vec3 reflectedDirection = -1.0f * (2.0f * (glm::dot(intersectionNormal,inDirection) * intersectionNormal) - inDirection);
	
	r->reflectionRay = new Ray(reflectedDirection, intersectionAt);

	if(transparent == true){
		//Refraction
		float n1 = 1.0f;
        float n2 = refractiveIndex;
        
        if(r->getInsideObject() == true){
            n1 = refractiveIndex;
            n2 = 1.0f;
        }

		float n = n1/n2;
		float cosI = glm::dot(intersectionNormal, inDirection);
		float sinT2 = 1.0f - n * n * (1.0f - cosI * cosI);

		if(sinT2 >= 0.0f){
			refractedDirection = n * inDirection - (n * cosI + (float)sqrt(sinT2)) * intersectionNormal;
			r->refractionRay = new Ray(refractedDirection, intersectionAt);
			if(r->getInsideObject() == false){
                r->refractionRay->setInsideObject(true);
            }else{
                r->refractionRay->setInsideObject(false);
            }
		}
	}
}