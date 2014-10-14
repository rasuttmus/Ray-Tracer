#include "room.h"

Room::Room(Rectangle *r0, Rectangle *r1, Rectangle *r2, Rectangle *r3, Rectangle *r4, glm::vec3 p, float s):
position(p), size(s)
{
    addWall(r0);
    addWall(r1);
    addWall(r2);
    addWall(r3);
    addWall(r4);
}

void Room::initRectangles() {

}

void Room::computeIntersections() {

}

void Room::addWall(Rectangle *r) {
    walls.push_back(r);
}
