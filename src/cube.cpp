#include "cube.h"

Cube::Cube(glm::vec3 p, float s, bool t, float ref): 
position(p), size(s), transparent(t), refractiveIndex(ref){ }

void Cube::initRectangleObjects(){
    addRectangle(new Rectangle(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    addRectangle(new Rectangle(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    addRectangle(new Rectangle(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f)));
    
    for(std::vector<Rectangle *>::iterator it = rectangles.begin(); it != rectangles.end(); ++it){
        for(std::vector<glm::vec3>::iterator it2 = (*it)->corners.begin(); it2 != (*it)->corners.end(); ++it2){
            (*it2).x = ((*it2).x * size) + position.x;
            (*it2).y = ((*it2).y * size) + position.y;
            (*it2).z = ((*it2).z * size) + position.z;
        }
    }
}

glm::vec3 Cube::calculateIntersections(glm::vec3 direction, glm::vec3 startingPoint){
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

void Cube::computeChildrenRays(Ray *r){
        
    glm::vec3 intersectionPoint(-2.0f, -2.0f, 2.0f);
    glm::vec3 intersectionNormal(0.0f, 0.0f, 0.0f);

    for(std::vector<Rectangle *>::iterator it = rectangles.begin(); it != rectangles.end(); ++it){

        if(glm::length(intersectionPoint - r->getStartingPoint()) > glm::length((*it)->calculateIntersections(r->getDirection(), r->getStartingPoint()) - r->getStartingPoint())){
            intersectionPoint = (*it)->calculateIntersections(r->getDirection(), r->getStartingPoint());
            intersectionNormal = (*it)->getNormal();
        }
    }

    glm::vec3 inDirection = glm::normalize(r->getDirection());
    glm::vec3 parentPos = r->getStartingPoint();
    glm::vec3 refractedDirection = glm::vec3(0.0f, 0.0f, 0.0f);
    
    glm::vec3 reflectedDirection = -1.0f * (2.0f * (glm::dot(intersectionNormal,inDirection) * intersectionNormal) - inDirection);
    
    r->reflectionRay = new Ray(reflectedDirection, intersectionPoint);

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
            r->refractionRay = new Ray(refractedDirection, intersectionPoint);
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

void Cube::setPosition(glm::vec3 p){
    position = p;
}

glm::vec3 Cube::getPosition(){
    return position;
}

int Cube::getType(){
    return CUBE_SHAPE;
}

glm::vec3 Cube::getIntersectionNormal(){
    return intersectionNormal;
}