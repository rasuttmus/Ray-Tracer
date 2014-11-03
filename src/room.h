#include "glm/glm.hpp"
#include <vector>
#include "rectangle.h"
#include "shape.h"

#ifndef ROOM_H
#define ROOM_H

#define ROOM_SHAPE 2

class Rectangle;

class Room: public Shape{
public:
    glm::dvec3 position;
    double size;
    std::vector<Rectangle *> walls;
    std::vector<glm::dvec3> wallColors;

    //constructor
    Room(glm::dvec3, double, glm::dvec3);
    Room(glm::dvec3, double, glm::dvec3, glm::dvec3, glm::dvec3, glm::dvec3, glm::dvec3);

    //methods
    void initRectangles();
    glm::dvec3 calculateIntersections(glm::dvec3 direction, glm::dvec3 startingPoint);
    void computeChildrenRays(Ray *);
    void addWall(Rectangle *);
   // glm::dvec3 getIntersectionNormal();

    int getType();
    glm::dvec3 getColor(int);

    int getWallIntersectionIndex();

    glm::dvec3 randomPosition();

    double getRefractiveIndex();

    glm::dvec3 getIntersectionNormal();

private:
    int wallIntersectionIndex;
    glm::dvec3 intersectionNormal;
};

#endif // ROOM_H