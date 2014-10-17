#include "glm/glm.hpp"
#include <vector>
#include "rectangle.h"

class Rectangle;

class Cube{
public:
    glm::vec3 position;
    float size;
    bool transparent;
    float refractiveIndex;
    std::vector<Rectangle *> rectangles;

    //constructors
    Cube(glm::vec3, float, bool, float);

    //methods
    void initRectangleObjects();
    void computeChildrenRays();
    void addRectangle(Rectangle *);
};