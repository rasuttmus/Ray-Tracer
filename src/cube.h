#include "glm/glm.hpp"
#include <vector>
#include "rectangle.h"
#include "ray.h"
#include "shape.h"

#ifndef CUBE_H
#define CUBE_H

#define CUBE_SHAPE 0
#define SPHERE_SHAPE 1

class Rectangle;

class Cube: public Shape{
public:
    float size;
    bool transparent;
    float refractiveIndex;
    std::vector<Rectangle *> rectangles;

    //constructors
    Cube(glm::vec3, float, bool, float = 0.0f);

    //methods
    void initRectangleObjects();
    glm::vec3 calculateIntersections(Ray *);
    void computeChildrenRays(Ray *, glm::vec3);
    void addRectangle(Rectangle *);
    void setPosition(glm::vec3);
    glm::vec3 getPosition();
    int getType();

private:
    glm::vec3 position;
};

#endif // CUBE_H