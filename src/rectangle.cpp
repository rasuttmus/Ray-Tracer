#include "rectangle.h"

Rectangle::Rectangle(glm::dvec3 c0, glm::dvec3 c1, glm::dvec3 c2, glm::dvec3 c3) {
    addCorner(c0);
    addCorner(c1);
    addCorner(c2);
    addCorner(c3);
}

void Rectangle::setNormal(glm::dvec3 norm){
    normal.x = norm.x;
    normal.y = norm.y;
    normal.z = norm.z;
}

glm::dvec3 Rectangle::getNormal(){
    return glm::dvec3(normal.x, normal.y, normal.z);
}

glm::dvec3 Rectangle::calculateIntersections(glm::dvec3 direction, glm::dvec3 startingPoint) {
    calcRectNormal();
    direction = glm::normalize(direction);

    glm::dvec3 intersectionPoint = glm::dvec3(-2.0,-2.0,2.0);
    glm::dvec3 possibleIntersection = glm::dvec3(0.0,0.0,0.0);

    double d = glm::dot(corners.at(0) - startingPoint, normal)/glm::dot(direction, normal);

    if(glm::dot(direction, normal) != 0.0){

        possibleIntersection = d * direction + startingPoint;

        // Round the intersection to 8 decimals to avoid precision errors
        possibleIntersection.x = std::floor(possibleIntersection.x * 100000000.0) / 100000000.0;
        possibleIntersection.y = std::floor(possibleIntersection.y * 100000000.0) / 100000000.0;
        possibleIntersection.z = std::floor(possibleIntersection.z * 100000000.0) / 100000000.0;
        
        if(possibleIntersection.x >= corners.at(0).x && possibleIntersection.y >= corners.at(0).y && possibleIntersection.z <= corners.at(0).z && possibleIntersection.x <= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z >= corners.at(2).z){
             //one intersection
            intersectionPoint = possibleIntersection;
        }
        if(possibleIntersection.x <= corners.at(1).x && possibleIntersection.y <= corners.at(1).y && possibleIntersection.z >= corners.at(1).z && possibleIntersection.x >= corners.at(3).x && possibleIntersection.y >= corners.at(3).y && possibleIntersection.z <= corners.at(3).z){
             //one intersection
            intersectionPoint = possibleIntersection;
        }

        if(possibleIntersection.x >= corners.at(1).x && possibleIntersection.y <= corners.at(1).y && possibleIntersection.z >= corners.at(1).z && possibleIntersection.x <= corners.at(3).x && possibleIntersection.y >= corners.at(3).y && possibleIntersection.z <= corners.at(3).z){
            //one intersection
            intersectionPoint = possibleIntersection;
        }
        if(possibleIntersection.x >= corners.at(0).x && possibleIntersection.y <= corners.at(0).y && possibleIntersection.z >= corners.at(0).z && possibleIntersection.x <= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z <= corners.at(2).z){
            //one intersection
            intersectionPoint = possibleIntersection;
        }
    }
    else{
        //no or a lot of intersections (ray parallell med plan)
    }

    return intersectionPoint;
}
void Rectangle::computeChildrenRays(Ray *ray, glm::dvec3 startingPoint) {
    // Calc new direction
    //glm::dvec3 direction = 2 * (glm::dot(normal, glm::dot(glm::normalize(ray->getDirection()), normal) - glm::normalize(ray->getDirection())) );

    //ray->reflectionRay = new Ray(direction, startingPoint);

    //if(ray->)
        //ray->refractionRay = new Ray();
}

void Rectangle::addCorner(glm::dvec3 c) {
    corners.push_back(c);
}

void Rectangle::calcRectNormal() {
    glm::dvec3 A = corners.at(0);
    glm::dvec3 B = corners.at(1);
    glm::dvec3 C = corners.at(3);

    glm::dvec3 AB = B - A;
    glm::dvec3 AC = C - A;

    normal = -1.0*glm::normalize((glm::cross(AB, AC)));

    //Fixing double decimal problem for normal
    normal.x = (int)normal.x;
    normal.y = (int)normal.y;
    normal.z = (int)normal.z;

}