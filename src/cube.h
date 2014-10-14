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
    Cube(Rectangle *, Rectangle *, Rectangle *, Rectangle *, Rectangle *, Rectangle *, glm::vec3, float, bool);

    //methods
    void initRectangleObjects();
    void computeChildrenRays();
    void addRectangle(Rectangle *);
};