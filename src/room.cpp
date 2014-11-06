#include "room.h"

Room::Room(glm::dvec3 p, double s, glm::dvec3 c):
position(p), size(s)
{
    initRectangles();

    for(int i = 0; i < 5; i++)
        wallColors.push_back(c);
}

Room::Room(glm::dvec3 p, double s, glm::dvec3 c0, glm::dvec3 c1, glm::dvec3 c2, glm::dvec3 c3, glm::dvec3 c4):
position(p), size(s)
{
    initRectangles();

    wallColors.push_back(c0);
    wallColors.push_back(c1);
    wallColors.push_back(c2);
    wallColors.push_back(c3);
    wallColors.push_back(c4);
}

void Room::initRectangles() {
    addWall(new Rectangle(glm::dvec3(0.0, 1.0, -1.0), glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, -1.0)));
    addWall(new Rectangle(glm::dvec3(0.0, 1.0, -1.0), glm::dvec3(1.0, 1.0, -1.0), glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(0.0, 1.0, 0.0)));
    addWall(new Rectangle(glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(1.0, 1.0, -1.0), glm::dvec3(1.0, 0.0, -1.0), glm::dvec3(1.0, 0.0, 0.0)));
    addWall(new Rectangle(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(1.0, 0.0, -1.0), glm::dvec3(0.0, 0.0, -1.0)));
    addWall(new Rectangle(glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(1.0, 1.0, 0.0), glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0)));
}

glm::dvec3 Room::calculateIntersections(Ray *r) {
    glm::dvec3 direction = glm::normalize(r->getDirection());
    glm::dvec3 startingPoint = r->getStartingPoint();
    glm::dvec3 intersectionPoint(-2.0, -2.0, 2.0);
    wallIntersectionIndex = 0;
    int counter = 0;

    for(std::vector<Rectangle *>::iterator it = walls.begin(); it != walls.end(); ++it){
        if(glm::length(intersectionPoint - startingPoint) > glm::length((*it)->calculateIntersections(direction, startingPoint, size) - startingPoint)){
            intersectionPoint = (*it)->calculateIntersections(direction, startingPoint, size);
            intersectionNormal = (*it)->getNormal();
            wallIntersectionIndex = counter;
        }
        counter++;
    }

    return intersectionPoint + intersectionNormal * -0.00000001;
}

void Room::addWall(Rectangle *r) {
    walls.push_back(r);
}

int Room::getType(){
    return ROOM_SHAPE;
}

void Room::computeChildrenRays(Ray *r){

}

glm::dvec3 Room::getColor(int wallIntersectionIndex){
    return wallColors.at(wallIntersectionIndex);
}

int Room::getWallIntersectionIndex(){
    return wallIntersectionIndex;
}

glm::dvec3 Room::randomPosition(){
    return glm::dvec3(0.0, 0.0, 0.0);
}

double Room::getRefractiveIndex(){
    return 1.0;
}

glm::dvec3 Room::getIntersectionNormal(){
    return intersectionNormal;
}

bool Room::getTransparency(){
    return false;
}