#include "rectangle.h"

Rectangle::Rectangle(glm::vec3 c0, glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) {
    addCorner(c0);
    addCorner(c1);
    addCorner(c2);
    addCorner(c3);
}

glm::vec3 Rectangle::calculateIntersections(Ray *ray) {
    float d = calcRectangleEquation();

    //glm::vec3 distanceFromOrigin();

    //glm::vec3 rectangleNormal();

    if(normal.x >= 0.0f || normal.y >= 0.0f || normal.z >= 0.0f)
        ray->setInsideObject(true);

    //glm::vec3 p0(rectangleEquation.x * 0.5, rectangleEquation.y * 0.5, rectangleEquation.z * -0.5);
    //std::cout << std::endl << "p0: " << "x: " << p0.x << "   y: " << p0.y << "   z: " << p0.z << std::endl;
    //std::cout << std::endl << "rectangleEquation.w: " << d << std::endl;

    //std::cout << std::endl << "täljare: " << (glm::dot((ray->getStartingPoint()), normal) + d) << std::endl;

    //std::cout << std::endl << "nämnare: " << (glm::dot(ray->getDirection(), normal)) << std::endl;

    float t = - (glm::dot((ray->getStartingPoint()), normal) + d) / (glm::dot(ray->getDirection(), normal));

    glm::vec3 intersectionPoint = ray->getStartingPoint() + t * ray->getDirection();

    if(normal.x >= 0.0f && normal.y >= 0.0f && normal.z >= 0.0f) {
        if(intersectionPoint.x >= corners.at(1).x && intersectionPoint.y <= corners.at(1).y && intersectionPoint.z >= corners.at(1).z && intersectionPoint.x <= corners.at(3).x && intersectionPoint.y >= corners.at(3).y && intersectionPoint.z <= corners.at(3).z){
            //std::cout << std::endl << "P: " << "x: " << intersectionPoint.x << "   y: " << intersectionPoint.y << "   z: " << intersectionPoint.z << std::endl;
            //std::cout << std::endl << "första, positiv normal!!!" << std::endl;
            ray->setIntersected(true);
            return intersectionPoint;
        }else{
            //std::cout << std::endl << " INGEN INTERSECTION! " << std::endl;
            return glm::vec3(10000.0f, 10000.0f, 10000.0f);
        }
    } else {
        if(intersectionPoint.x >= corners.at(0).x && intersectionPoint.y <= corners.at(0).y && intersectionPoint.z <= corners.at(0).z && intersectionPoint.x <= corners.at(2).x && intersectionPoint.y >= corners.at(2).y && intersectionPoint.z >= corners.at(2).z){
            //std::cout << std::endl << "P: " << "x: " << intersectionPoint.x << "   y: " << intersectionPoint.y << "   z: " << intersectionPoint.z << std::endl;
            //std::cout << std::endl << "andra, negativ normal!!!" << std::endl;
            ray->setIntersected(true);
            return intersectionPoint;
        } else {
            //std::cout << std::endl << " INGEN INTERSECTION! " << std::endl;
            return glm::vec3(10000.0f, 10000.0f, 10000.0f);
        }
    }
    return glm::vec3(10000.0f, 10000.0f, 10000.0f);
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

float Rectangle::calcRectangleEquation() {

    /*for(std::vector<glm::vec3>::iterator it = corners.begin(); it != corners.end(); ++it) {
        std::cout << "TJENA: " << (*it).x << std::endl;
    }*/

    glm::vec3 A = corners.at(0);
    glm::vec3 B = corners.at(1);
    glm::vec3 C = corners.at(3);

    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;

    //std::cout << std::endl << "AB: " << "x: " << AB.x << "   y: " << AB.y << "   z: " << AB.z << std::endl;
    //std::cout << std::endl << "AC: " << "x: " << AC.x << "   y: " << AC.y << "   z: " << AC.z << std::endl;

    normal = glm::normalize(glm::cross(AB, AC));

    //std::cout << std::endl << "normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;

    // assumes the form: x + y + z + d = 0
    // instead of x + y + z = d
    float d = -(normal.x * A.x + normal.y * A.y + normal.z * A.z);

    //std::cout << "d: " << d << std::endl;

    //std::cout << "RECTANGLE EQ: " << "x: " << normal.x << "   y: " << normal.y << "   z: " << normal.z << "   d: " << d << std::endl;

    return d;
}