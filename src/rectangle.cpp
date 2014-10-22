#include "rectangle.h"

Rectangle::Rectangle(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) {
    addCorner(c0);
    addCorner(c1);
    addCorner(c2);
    addCorner(c3);
}

glm::vec3 Rectangle::calculateIntersections(glm::vec3 direction, glm::vec3 startingPoint) {
    calcRectangleEquation();

    glm::vec3 intersectionPoint = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 possibleIntersection = glm::vec3(0.0f,0.0f,0.0f);

    float d = glm::dot(corners.at(0) - startingPoint, normal)/glm::dot(direction, normal);



/*
    if(glm::dot(direction, normal) != 0.0f){
        possibleIntersection = d * direction + startingPoint;
        std::cout << "possible intersection: " << "x: " << possibleIntersection.x << "   y: " << possibleIntersection.y << "   z: " << possibleIntersection.z << std::endl; 

        if(possibleIntersection.x <= corners.at(0).x && possibleIntersection.y <= corners.at(0).y && possibleIntersection.z >= corners.at(0).z && possibleIntersection.x >= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z <= corners.at(2).z){
             //one intersection
            intersectionPoint = d * direction + startingPoint;
            std::cout << "one intersection!"; 
        }
        if(possibleIntersection.x <= corners.at(1).x && possibleIntersection.y <= corners.at(1).y && possibleIntersection.z >= corners.at(1).z && possibleIntersection.x >= corners.at(3).x && possibleIntersection.y >= corners.at(3).y && possibleIntersection.z <= corners.at(3).z){
             //one intersection
            intersectionPoint = d * direction + startingPoint;
            std::cout << "one intersection!"; 
        }

        if(possibleIntersection.x >= corners.at(1).x && possibleIntersection.y <= corners.at(1).y && possibleIntersection.z >= corners.at(1).z && possibleIntersection.x <= corners.at(3).x && possibleIntersection.y >= corners.at(3).y && possibleIntersection.z <= corners.at(3).z){
            //one intersection
            std::cout << "one intersection" ;
            intersectionPoint = d * direction + startingPoint;
        }
        if(possibleIntersection.x >= corners.at(0).x && possibleIntersection.y <= corners.at(0).y && possibleIntersection.z >= corners.at(0).z && possibleIntersection.x <= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z <= corners.at(2).z){
            //one intersection
            std::cout << "one intersection" ;
            intersectionPoint = d * direction + startingPoint;
        }
    }
    */
    if(glm::dot(direction, normal) != 0.0f){
        possibleIntersection = d * direction + startingPoint;
        std::cout << "possible intersection: " << "x: " << possibleIntersection.x << "   y: " << possibleIntersection.y << "   z: " << possibleIntersection.z << std::endl; 
        // BORDE FUNKA
        if(possibleIntersection.x >= corners.at(0).x && possibleIntersection.y >= corners.at(0).y && possibleIntersection.z <= corners.at(0).z && possibleIntersection.x <= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z >= corners.at(2).z){
             //one intersection
            intersectionPoint = d * direction + startingPoint;
            std::cout << "if 1, one intersection!"; 
        }
        if(possibleIntersection.x <= corners.at(1).x && possibleIntersection.y <= corners.at(1).y && possibleIntersection.z >= corners.at(1).z && possibleIntersection.x >= corners.at(3).x && possibleIntersection.y >= corners.at(3).y && possibleIntersection.z <= corners.at(3).z){
             //one intersection
            intersectionPoint = d * direction + startingPoint;
            std::cout << "if 2, one intersection!"; 
        }

        if(possibleIntersection.x >= corners.at(1).x && possibleIntersection.y <= corners.at(1).y && possibleIntersection.z >= corners.at(1).z && possibleIntersection.x <= corners.at(3).x && possibleIntersection.y >= corners.at(3).y && possibleIntersection.z <= corners.at(3).z){
            //one intersection
            std::cout << "if 3, one intersection" ;
            intersectionPoint = d * direction + startingPoint;
        }
        if(possibleIntersection.x >= corners.at(0).x && possibleIntersection.y <= corners.at(0).y && possibleIntersection.z >= corners.at(0).z && possibleIntersection.x <= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z <= corners.at(2).z){
            //one intersection
            std::cout << "if 4, one intersection" ;
            intersectionPoint = d * direction + startingPoint;
        }
    }
    else{
        //no or a lot of intersections (ray parallell med plan)
       std::cout << "no intersections!";
    }

    return intersectionPoint;
}

void Rectangle::computeChildrenRays() {

}

void Rectangle::addCorner(glm::vec3 c) {
    corners.push_back(c);
}

void Rectangle::calcRectangleEquation() {


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