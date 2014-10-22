#include "rectangle.h"

Rectangle::Rectangle(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) {
    addCorner(c0);
    addCorner(c1);
    addCorner(c2);
    addCorner(c3);
}

void Rectangle::setNormal(glm::vec3 norm){
    normal.x = norm.x;
    normal.y = norm.y;
    normal.z = norm.z;
}

glm::vec3 Rectangle::getNormal(){
    return glm::vec3(normal.x, normal.y, normal.z);
}

glm::vec3 Rectangle::calculateIntersections(glm::vec3 direction, glm::vec3 startingPoint) {
    calcRectNormal();

    glm::vec3 intersectionPoint = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 possibleIntersection = glm::vec3(0.0f,0.0f,0.0f);

    float d = glm::dot(corners.at(0) - startingPoint, normal)/glm::dot(direction, normal);

    if(glm::dot(direction, normal) != 0.0f){
        possibleIntersection = d * direction + startingPoint;
      
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
void Rectangle::computeChildrenRays(Ray *ray, glm::vec3 startingPoint) {
    // Calc new direction
    //glm::vec3 direction = 2 * (glm::dot(normal, glm::dot(glm::normalize(ray->getDirection()), normal) - glm::normalize(ray->getDirection())) );

    //ray->reflectionRay = new Ray(direction, startingPoint);

    //if(ray->)
        //ray->refractionRay = new Ray();
}

void Rectangle::addCorner(glm::vec3 c) {
    corners.push_back(c);
}

void Rectangle::calcRectNormal() {
    glm::vec3 A = corners.at(0);
    glm::vec3 B = corners.at(1);
    glm::vec3 C = corners.at(3);

    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;

    normal = -1.0f*glm::normalize((glm::cross(AB, AC)));

    //Fixing float decimal problem for normal
    normal.x = (int)normal.x;
    normal.y = (int)normal.y;
    normal.z = (int)normal.z;

}