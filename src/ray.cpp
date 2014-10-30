#include "ray.h"

Ray::Ray(glm::dvec3 d, glm::dvec3 s):
		 direction(d), startingPoint(s){
}

void Ray::calculateColor(glm::dvec3 intersectionPoint, glm::dvec3 lightPos) {

//recursive function thats goes through all child rays. 
color = glm::dvec3(0.0, 0.0, 0.0);
/*
    if(finalNode){

    }

    if(!finalNode){
        color1 * importance = reflectionRay->calculateColor();
        color2 * importance = refractionRay->calculateColor();  
        color = color1 + color2;
        calculateLocalContribution();
    }
     */
}

glm::dvec3 Ray::calculateLocalContribution(glm::dvec3 intersectionPoint, glm::dvec3 lightPos){
    return lightPos - intersectionPoint;
}

void Ray::setStartingPoint(glm::dvec3 s){
    startingPoint = s;
}

glm::dvec3 Ray::getStartingPoint(){
    return startingPoint;
}

void Ray::setDirection(glm::dvec3 d){
    direction = d;
}

glm::dvec3 Ray::getDirection(){
    return direction;
}

void Ray::setInsideObject(bool i){
    insideObject = i;
}

bool Ray::getInsideObject(){
    return insideObject;
}

void Ray::setIntersected(bool i){
    intersected = i;
}

bool Ray::getIntersected(){
    return intersected;
}

void Ray::setFinalNode(bool f){
    finalNode = f;
}

bool Ray::getFinalNode(){
    return finalNode;
}

void Ray::setImportance(double i){
    importance = i;
}


double Ray::getImportance(){
    return importance;
}

void Ray::setColor(glm::dvec3 c){
    color = c;
}

glm::dvec3 Ray::getColor(){
    return color;
}