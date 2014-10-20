#include "glm/glm.hpp"
#include <vector>
#include "rectangle.h"
#include "ray.h"

class Rectangle;

class Cube{
public:
    glm::vec3 position;
    float size;
    bool transparent;
    float refractiveIndex;
    std::vector<Rectangle *> rectangles;

    //constructors
    Cube(glm::vec3, float, bool, float = 0.0f);

    //methods
    void initRectangleObjects();
    void computeChildrenRays(Ray *);
    void addRectangle(Rectangle *);
};