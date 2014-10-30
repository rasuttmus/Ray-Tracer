#include "room.h"

Room::Room(glm::dvec3 p, double s):
position(p), size(s)
{
    initRectangles();
}

void Room::initRectangles() {
    /*
    addWall(new Rectangle(glm::dvec3(0.0f, 1.0f, -1.0f), glm::dvec3(0.0f, 1.0f, 0.0f), glm::dvec3(0.0f, 0.0f, 0.0f), glm::dvec3(0.0f, 0.0f, -1.0f)));
    addWall(new Rectangle(glm::dvec3(0.0f, 1.0f, -1.0f), glm::dvec3(1.0f, 1.0f, -1.0f), glm::dvec3(1.0f, 1.0f, 0.0f), glm::dvec3(0.0f, 1.0f, 0.0f)));
    addWall(new Rectangle(glm::dvec3(1.0f, 1.0f, 0.0f), glm::dvec3(1.0f, 1.0f, -1.0f), glm::dvec3(1.0f, 0.0f, -1.0f), glm::dvec3(1.0f, 0.0f, 0.0f)));
    addWall(new Rectangle(glm::dvec3(0.0f, 0.0f, 0.0f), glm::dvec3(1.0f, 0.0f, 0.0f), glm::dvec3(1.0f, 0.0f, -1.0f), glm::dvec3(0.0f, 0.0f, -1.0f)));
    addWall(new Rectangle(glm::dvec3(0.0f, 1.0f, 0.0f), glm::dvec3(1.0f, 1.0f, 0.0f), glm::dvec3(1.0f, 0.0f, 0.0f), glm::dvec3(0.0f, 0.0f, 0.0f)));*/
    addWall(new Rectangle(glm::dvec3(0.0, 1.0, -1.0), glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, -1.0)));
    addWall(new Rectangle(glm::dvec3(0.0, 1.0, -1.0), glm::dvec3(1.0, 1.0, -1.0), glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(0.0, 1.0, 0.0)));
    addWall(new Rectangle(glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(1.0, 1.0, -1.0), glm::dvec3(1.0, 0.0, -1.0), glm::dvec3(1.0, 0.0, 0.0)));
    addWall(new Rectangle(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(1.0, 0.0, -1.0), glm::dvec3(0.0, 0.0, -1.0)));
    addWall(new Rectangle(glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0)));
}

glm::dvec3 Room::calculateIntersections(glm::dvec3 direction, glm::dvec3 startingPoint) {
    direction = glm::normalize(direction);
    glm::dvec3 intersectionPoint(-2.0, -2.0, 2.0);
    for(std::vector<Rectangle *>::iterator it = walls.begin(); it != walls.end(); ++it){
        if(glm::length(intersectionPoint - startingPoint) > glm::length((*it)->calculateIntersections(direction, startingPoint, size) - startingPoint)){
            intersectionPoint = (*it)->calculateIntersections(direction, startingPoint, size);
            //intersectionNormal = (*it)->getNormal();
        }
    }
    //std::cout << std::endl << "Room Hit!" << "  x: " << intersectionPoint.x << "   y: " << intersectionPoint.y << "   z: " << intersectionPoint.z << std::endl;

    return intersectionPoint;
}

void Room::addWall(Rectangle *r) {
    walls.push_back(r);
}

int Room::getType(){
    return ROOM_SHAPE;
}

void Room::computeChildrenRays(Ray *r){

}

/*glm::dvec3 getIntersectionNormal(){
    return glm::dvec3(0.0f, 0.0f, 0.0f);
}*/