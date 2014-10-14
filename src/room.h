#include "glm/glm.hpp"
#include <vector>
#include "rectangle.h"

#ifndef ROOM_H
#define ROOM_H

class Rectangle;

class Room{
public:
    glm::vec3 position;
    float size;
    std::vector<Rectangle *> walls;

    //constructor
    Room(Rectangle *, Rectangle *, Rectangle *, Rectangle *, Rectangle *, glm::vec3, float);

    //methods
    void initRectangles();
    void computeIntersections();
    void addWall(Rectangle *);
};

#endif // ROOM_H