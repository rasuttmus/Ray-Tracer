#include "room.h"

Room::Room(glm::vec3 p, float s):
position(p), size(s)
{
    initRectangles();
}

void Room::initRectangles() {
    wall1 = new Rectangle(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    wall2 = new Rectangle(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    wall3 = new Rectangle(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wall4 = new Rectangle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    wall5 = new Rectangle(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

void Room::computeIntersections() {

}

void Room::addWall(Rectangle *r) {
    walls.push_back(r);
}
