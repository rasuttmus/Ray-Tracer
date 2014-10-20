#include "room.h"

Room::Room(glm::vec3 p, float s):
position(p), size(s)
{
    initRectangles();
}

void Room::initRectangles() {
    addWall(new Rectangle(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    addWall(new Rectangle(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    addWall(new Rectangle(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    addWall(new Rectangle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    addWall(new Rectangle(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

    //walls.at(0)->calculateIntersections();
}

void Room::computeIntersections() {

}

void Room::addWall(Rectangle *r) {
    walls.push_back(r);
}
