#include "light.h"

Light::Light(double r, glm::dvec3 p, double s): 
radiance(r), position(p), size(s)
{
    glm::dvec3 p0(0.0 * size + position.x, position.y, -1.0 * size + position.z);
    glm::dvec3 p1(1.0 * size + position.x, position.y, -1.0 * size + position.z);
    glm::dvec3 p2(1.0 * size + position.x, position.y, 0.0 * size + position.z);
    glm::dvec3 p3(0.0 * size + position.x, position.y, 0.0 * size + position.z);

    lightObject = new Rectangle(p0, p1, p2, p3);
    srand((time(NULL)));
}

glm::dvec3 Light::randomPosition() {

    glm::dvec3 randPos(0.0, 0.0, 0.0);
    //srand((time(NULL)));

    randPos.x = lightObject->corners.at(0).x + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / ((lightObject->corners.at(1).x) - lightObject->corners.at(0).x)));
    randPos.y = position.y;
    randPos.z = lightObject->corners.at(2).z + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / ((lightObject->corners.at(1).z) - lightObject->corners.at(2).z)));

    // use this for point light
    //return glm::dvec3(0.5, position.y, -0.5);

    // use this for smooth shadow
    return randPos;
}

glm::dvec3 Light::calculateIntersections(Ray *r){
    glm::dvec3 intersectionPoint = lightObject->calculateIntersections(glm::normalize(r->getDirection()), r->getStartingPoint(), size);

    return intersectionPoint;
}

void Light::computeChildrenRays(Ray *r){

}

int Light::getType(){
    return LIGHT_SHAPE;
}

glm::dvec3 Light::getColor(int c){
    return glm::dvec3(1.0, 1.0, 1.0);
}

int Light::getWallIntersectionIndex(){
    return 1;
}

double Light::getRefractiveIndex(){
    return 1.0;
}

glm::dvec3 Light::getIntersectionNormal(){
    return glm::dvec3(0.0, 0.0, 0.0);
}

bool Light::getTransparency(){
    return false;
}

