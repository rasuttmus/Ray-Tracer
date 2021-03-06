#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include <vector>
#include "rectangle.h"
#include "ray.h"
#include "shape.h"

#ifndef CUBE_H
#define CUBE_H

#define CUBE_SHAPE 0
#define SPHERE_SHAPE 1
#define ROOM_SHAPE 2

class Rectangle;

class Cube: public Shape{
public:
    double size;
    std::vector<Rectangle *> rectangles;
    std::vector<glm::dvec3> rectangleColors;

    //constructors
    Cube(glm::dvec3, double, bool, glm::dvec3, double = 0.0);
    Cube(glm::dvec3, double, bool, glm::dvec3, glm::dvec3, glm::dvec3, glm::dvec3, glm::dvec3, glm::dvec3, double = 0.0);

    //methods
    void initRectangleObjects();
    glm::dvec3 calculateIntersections(Ray *);
    void computeChildrenRays(Ray *);
    void addRectangle(Rectangle *);

    void setPosition(glm::dvec3);
    glm::dvec3 getPosition();
    
    int getType();
    
    int getWallIntersectionIndex();
    
    glm::dvec3 getColor(int);
    
    glm::dvec3 randomPosition();

    double getRefractiveIndex();

    glm::dvec3 getIntersectionNormal();

    bool getTransparency();

private:
    glm::dvec3 position;
    glm::dvec3 intersectionNormal;
    int wallIntersectionIndex;
    double refractiveIndex;
    bool transparent;
};

#endif // CUBE_H