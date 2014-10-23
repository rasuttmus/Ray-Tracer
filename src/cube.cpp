#include "cube.h"

Cube::Cube(glm::dvec3 p, double s, bool t, double ref): 
position(p), size(s), transparent(t), refractiveIndex(ref)
{ 
    initRectangleObjects();
}

void Cube::initRectangleObjects(){
    addRectangle(new Rectangle(glm::dvec3(0.0, 1.0, -1.0), glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, -1.0)));
    addRectangle(new Rectangle(glm::dvec3(0.0, 1.0, -1.0), glm::dvec3(1.0, 1.0, -1.0), glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(0.0, 1.0, 0.0)));
    addRectangle(new Rectangle(glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(1.0, 1.0, -1.0), glm::dvec3(1.0, 0.0, -1.0), glm::dvec3(1.0, 0.0, 0.0)));
    addRectangle(new Rectangle(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(1.0, 0.0, -1.0), glm::dvec3(0.0, 0.0, -1.0)));
    addRectangle(new Rectangle(glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0)));
    addRectangle(new Rectangle(glm::dvec3(1.0, 1.0, -1.0), glm::dvec3(0.0, 1.0, -1.0), glm::dvec3(0.0, 0.0, -1.0), glm::dvec3(1.0, 0.0, -1.0)));
    
    for(std::vector<Rectangle *>::iterator it = rectangles.begin(); it != rectangles.end(); ++it){
        for(std::vector<glm::dvec3>::iterator it2 = (*it)->corners.begin(); it2 != (*it)->corners.end(); ++it2){
            (*it2).x = ((*it2).x * size) + position.x;
            (*it2).y = ((*it2).y * size) + position.y;
            (*it2).z = ((*it2).z * size) + position.z;
        }
    }
}

glm::dvec3 Cube::calculateIntersections(glm::dvec3 direction, glm::dvec3 startingPoint){
    direction = glm::normalize(direction);
    glm::dvec3 intersectionPoint(-2.0, -2.0, 2.0);
    for(std::vector<Rectangle *>::iterator it = rectangles.begin(); it != rectangles.end(); ++it){

        if(glm::length(intersectionPoint - startingPoint) > glm::length((*it)->calculateIntersections(direction, startingPoint) - startingPoint)){
            intersectionPoint = (*it)->calculateIntersections(direction, startingPoint);
            //intersectionNormal = (*it)->getNormal();
        }
    }
    //std::cout << std::endl << "Cube Hit!" << "   x: " << intersectionPoint.x << "   y: " << intersectionPoint.y << "   z: " << intersectionPoint.z << std::endl;

    return intersectionPoint;
}

void Cube::computeChildrenRays(Ray *r){
        
    glm::dvec3 intersectionAt = calculateIntersections(r->getDirection(), r->getStartingPoint());

    glm::dvec3 inDirection = glm::normalize(r->getDirection());
    glm::dvec3 parentPos = r->getStartingPoint();
    glm::dvec3 refractedDirection = glm::dvec3(0.0, 0.0, 0.0);
    
    glm::dvec3 reflectedDirection = -1.0 * (2.0 * (glm::dot(intersectionNormal,inDirection) * intersectionNormal) - inDirection);
    
    r->reflectionRay = new Ray(reflectedDirection, intersectionAt);

    if(transparent == true){
        //Refraction
        double n1 = 1.0;
        double n2 = refractiveIndex;
        
        if(r->getInsideObject() == true){
            n1 = refractiveIndex;
            n2 = 1.0;
        }
        
        double n = n1/n2;
        double cosI = glm::dot(intersectionNormal, inDirection);
        double sinT2 = 1.0 - n * n * (1.0 - cosI * cosI);

        if(sinT2 >= 0.0){
            refractedDirection = n * inDirection - (n * cosI + (double)sqrt(sinT2)) * intersectionNormal;
            r->refractionRay = new Ray(refractedDirection, intersectionAt);
            if(r->getInsideObject() == false){
                r->refractionRay->setInsideObject(true);
            }else{
                r->refractionRay->setInsideObject(false);
            }
        }
    }
}

void Cube::addRectangle(Rectangle *r){
    rectangles.push_back(r);
}

void Cube::setPosition(glm::dvec3 p){
    position = p;
}

glm::dvec3 Cube::getPosition(){
    return position;
}

int Cube::getType(){
    return CUBE_SHAPE;
}

/*glm::dvec3 Cube::getIntersectionNormal(){
    return intersectionNormal;
}*/