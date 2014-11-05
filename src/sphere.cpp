#include "sphere.h"


Sphere::Sphere(glm::dvec3 p, double r, bool t, double ref, glm::dvec3 c): 
position(p), radius(r), transparent(t), refractiveIndex(ref), color(c)
{ 
	Ray *roy = new Ray(glm::dvec3(0.0,0.0,1.0), glm::dvec3(0.0,0.0,-1.0));
	computeChildrenRays(roy);
}

glm::dvec3 Sphere::calculateIntersections(Ray *r) {

	glm::dvec3 intersectionPoint = glm::dvec3(-2.0, -2.0, 2.0); 
    glm::dvec3 direction = glm::normalize(r->getDirection());
    glm::dvec3 startingPoint = r->getStartingPoint();

	double b = 2 * (direction.x * (startingPoint.x - position.x) + direction.y * (startingPoint.y - position.y) + direction.z * (startingPoint.z - position.z));
	double c = pow((startingPoint.x - position.x),2) + pow((startingPoint.y - position.y),2) + pow((startingPoint.z - position.z),2) - pow(radius,2);
	double t = 0.0;
	
	if((b * b) - (4 * c) < 0.0){
		//no intersections
	}
	else if((b * b) - (4 * c) == 0.0){
		//one tangential intersection
		intersectionPoint = startingPoint + (direction * (-b/2));
	}
	else{
		//two intersections
			t = (-b + sqrt((b * b) - (4 * c)))/2;
			if(t > 0){
				intersectionPoint = startingPoint + (direction * t);
			}
			
			t = (-b - sqrt((b * b) - (4 * c)))/2;
			if(t > 0){
			intersectionPoint = startingPoint + (direction * t);
			}
	}
    glm::dvec3 intersectionNormal = glm::normalize(intersectionPoint - position);
    
    intersectionNormal.x = round(intersectionNormal.x * 100000000.0) / 100000000.0;
    intersectionNormal.y = round(intersectionNormal.y * 100000000.0) / 100000000.0;
    intersectionNormal.z = round(intersectionNormal.z * 100000000.0) / 100000000.0;

    intersectionNormal = glm::normalize(intersectionNormal);

    if(r->getInsideObject()){
        //intersectionNormal = -intersectionNormal;
        //std::cout << std::endl << "inside" << std::endl;
        //std::cout << std::endl << "normal: (" << intersectionNormal.x << ", " << intersectionNormal.y << ", " << intersectionNormal.z << ")" << std::endl;
    }
    /*std::cout << "normal: (" << intersectionNormal.x << ", " << intersectionNormal.y << ", " << intersectionNormal.z << ")" << std::endl;
    std::cout << "intersection: (" << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << ")" << std::endl;*/
    //std::cout << std::endl << "Sphere Hit!" << "x: " << intersectionPoint.x << "   y: " << intersectionPoint.y << "   z: " << intersectionPoint.z << std::endl;
	
    //return intersectionPoint + (glm::normalize(intersectionNormal) * 0.0001);
    return intersectionPoint;
	
}

void Sphere::computeChildrenRays(Ray *r) {

	glm::dvec3 inDirection = glm::normalize(r->getDirection());
	glm::dvec3 parentPos = r->getStartingPoint();
	glm::dvec3 refractedDirection = glm::dvec3(0.0, 0.0, 0.0);

	glm::dvec3 intersectionAt = calculateIntersections(r);
	
	intersectionNormal = glm::normalize(intersectionAt - position);

    intersectionNormal.x = std::floor(intersectionNormal.x * 100000000.0) / 100000000.0;
    intersectionNormal.y = std::floor(intersectionNormal.y * 100000000.0) / 100000000.0;
    intersectionNormal.z = std::floor(intersectionNormal.z * 100000000.0) / 100000000.0;


	if(transparent == true){
		//Refraction
		double n1 = 1.0;
        double n2 = refractiveIndex;
        
        if(r->getInsideObject() == true){
            n1 = refractiveIndex;
            n2 = 1.0;
            intersectionNormal = -intersectionNormal;
        }

		double n = n1/n2;
		double cosI = glm::dot(intersectionNormal, inDirection);
		double sinT2 = 1.0 - n * n * (1.0 - cosI * cosI);

		if(sinT2 >= 0.0){
			refractedDirection = n * inDirection - (n * cosI + (double)sqrt(sinT2)) * intersectionNormal;
            /*refractedDirection = glm::refract(glm::vec3((float)inDirection.x, (float)inDirection.y, (float)inDirection.z), 
                                 glm::vec3((float)intersectionNormal.x, (float)intersectionNormal.y, (float)intersectionNormal.z),
                                 (float)refractiveIndex);*/
            //std::cout << "refractedDirection: (" << refractedDirection.x << ", " << refractedDirection.y << ", " << refractedDirection.z << ")" << std::endl;
            r->refractionRay = new Ray(refractedDirection, intersectionAt - (intersectionNormal) * 0.0002);
            
			if(r->getInsideObject() == false){
                r->refractionRay->setInsideObject(true);
                //r->reflectionRay->setInsideObject(false);
            }else{
                r->refractionRay->setInsideObject(false);
                //r->reflectionRay->setInsideObject(true);
            }
		}
	}
    glm::dvec3 reflectedDirection = -1.0 * (2.0 * (glm::dot(intersectionNormal,inDirection) * intersectionNormal) - inDirection);
    
    // Move the starting pos out from the object a bit, to avoid infinite bounces in on point
    r->reflectionRay = new Ray(reflectedDirection, intersectionAt + (intersectionNormal) * 0.00000001);
    //std::cout << "reflectedDirection: " << reflectedDirection.x << ", " << reflectedDirection.y << ", " << reflectedDirection.z << ")" << std::endl;
    if(r->getInsideObject() == false){
        r->reflectionRay->setInsideObject(false);
        //r->reflectionRay->setInsideObject(false);
    }else{
        r->reflectionRay->setInsideObject(true);
        //r->reflectionRay->setInsideObject(true);
    }
}

void Sphere::setPosition(glm::dvec3 p){
    position = p;
}

glm::dvec3 Sphere::getPosition(){
    return position;
}

int Sphere::getType(){
    return SPHERE_SHAPE;
}

void Sphere::setColor(glm::dvec3 c){
    color = c;
}

glm::dvec3 Sphere::getColor(int wallIntersectionIndex){
    return color;
}

int Sphere::getWallIntersectionIndex(){
    return 0;
}

glm::dvec3 Sphere::randomPosition(){
    return glm::dvec3(0.0, 0.0, 0.0);
}

double Sphere::getRefractiveIndex(){
    return refractiveIndex;
}

glm::dvec3 Sphere::getIntersectionNormal(){
    return intersectionNormal;
}

bool Sphere::getTransparency(){
    return transparent;
}

/*glm::dvec3 Sphere::getIntersectionNormal(){
    return intersectionNormal;
}*/