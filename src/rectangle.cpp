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
        /*possibleIntersection.x = std::floor(possibleIntersection.x * 100000000.0) / 100000000.0;
        possibleIntersection.y = std::floor(possibleIntersection.y * 100000000.0) / 100000000.0;
        possibleIntersection.z = std::floor(possibleIntersection.z * 100000000.0) / 100000000.0;*/
        possibleIntersection.x = std::floor(possibleIntersection.x * 100000.0 + 0.5) / 100000.0;
        possibleIntersection.y = std::floor(possibleIntersection.y * 100000.0 + 0.5) / 100000.0;
        possibleIntersection.z = std::floor(possibleIntersection.z * 100000.0 + 0.5) / 100000.0;
        //std::cout << std::endl << "possibleIntersection: " << "(" << possibleIntersection.x << ", " << possibleIntersection.y << ", " << possibleIntersection.z << ")" << std::endl;
        
        if(possibleIntersection.x * direction.x >= startingPoint.x * direction.x && possibleIntersection.y * direction.y >= startingPoint.y * direction.y && possibleIntersection.z * direction.z >= startingPoint.z * direction.z){
            // TA BORT 3 FÖRSTA KANSKE YOO
            if(possibleIntersection.x >= corners.at(0).x && possibleIntersection.y >= corners.at(0).y && possibleIntersection.z <= corners.at(0).z && possibleIntersection.x <= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z >= corners.at(2).z){
                 //one intersection
                //std::cout << std::endl << "if1" << std::endl;
                intersectionPoint = possibleIntersection;
            }
            if(possibleIntersection.x <= corners.at(1).x && possibleIntersection.y <= corners.at(1).y && possibleIntersection.z >= corners.at(1).z && possibleIntersection.x >= corners.at(3).x && possibleIntersection.y >= corners.at(3).y && possibleIntersection.z <= corners.at(3).z){
                 //one intersection
                //std::cout << std::endl << "if2" << std::endl;
                intersectionPoint = possibleIntersection;
            }
            if(possibleIntersection.x >= corners.at(1).x && possibleIntersection.y <= corners.at(1).y && possibleIntersection.z >= corners.at(1).z && possibleIntersection.x <= corners.at(3).x && possibleIntersection.y >= corners.at(3).y && possibleIntersection.z <= corners.at(3).z){
                //one intersection
                //std::cout << std::endl << "if3" << std::endl;
                intersectionPoint = possibleIntersection;
            }
            if(possibleIntersection.x >= corners.at(0).x && possibleIntersection.y <= corners.at(0).y && possibleIntersection.z >= corners.at(0).z && possibleIntersection.x <= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z <= corners.at(2).z){
                //one intersection
                //std::cout << std::endl << "if4" << std::endl;
                intersectionPoint = possibleIntersection;
            }
            if(possibleIntersection.x <= corners.at(0).x && possibleIntersection.y <= corners.at(0).y && possibleIntersection.z >= corners.at(0).z && possibleIntersection.x >= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z >= corners.at(2).z){
                //one intersection
                //std::cout << std::endl << "if5" << std::endl;
                intersectionPoint = possibleIntersection;
            }
            if(possibleIntersection.x <= corners.at(0).x && possibleIntersection.y <= corners.at(0).y && possibleIntersection.z <= corners.at(0).z && possibleIntersection.x <= corners.at(2).x && possibleIntersection.y >= corners.at(2).y && possibleIntersection.z >= corners.at(2).z){
                //one intersection
                //std::cout << std::endl << "if5" << std::endl;
                intersectionPoint = possibleIntersection;
            }
            if(possibleIntersection.x >= corners.at(0).x && possibleIntersection.y <= corners.at(0).y && possibleIntersection.z >= corners.at(0).z && possibleIntersection.x <= corners.at(2).x && possibleIntersection.y <= corners.at(2).y && possibleIntersection.z <= corners.at(2).z){
                //one intersection
                //std::cout << std::endl << "if5" << std::endl;
                intersectionPoint = possibleIntersection;
            }

            //std::cout << std::endl << "intersection point: " << "(" << intersectionPoint.x << "," << intersectionPoint.y << "," << intersectionPoint.z << ")" << std::endl;
            //std::cout << std::endl << "corner1-z: " << corners.at(0).z << "   corner2-z: " << corners.at(1).z << "   corner3-z: " << corners.at(2).z << "   corner4-z: " << corners.at(3).z << std::endl;
            //std::cout << std::endl << "(" << corners.at(0).x << ", " << corners.at(0).y << ", " << corners.at(0).z << ")" << std::endl;
            //std::cout << std::endl << "(" << corners.at(1).x << ", " << corners.at(1).y << ", " << corners.at(1).z << ")" << std::endl;
            //std::cout << std::endl << "(" << corners.at(2).x << ", " << corners.at(2).y << ", " << corners.at(2).z << ")" << std::endl;
            //std::cout << std::endl << "(" << corners.at(3).x << ", " << corners.at(3).y << ", " << corners.at(3).z << ")" << std::endl;
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