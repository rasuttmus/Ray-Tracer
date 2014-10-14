#include "glm/glm.hpp"

class Sphere{
public:
    //Instance variables
    glm::vec3 position;
    float radius;
    bool transparency;  
    float refractiveIndex;

    //contructor
    Sphere();

    //Instance methods
    void calculateIntersections();
    void calculateChildrenRays();

};