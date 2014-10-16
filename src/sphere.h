#include "glm/glm.hpp"

class Sphere{
public:
    //Instance variables
    glm::vec3 position;
    float radius;
    bool transparency;  
    float refractiveIndex;

    //contructor
    Sphere(glm::vec3, float, bool, float);

    //Instance methods
    void calculateIntersections();
    void calculateChildrenRays();

};