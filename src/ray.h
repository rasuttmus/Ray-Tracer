#include <iostream>
#include "glm/glm.hpp"

class Ray{
public:
    //Instance variables
    glm::vec3 startingPoint;
    glm::vec3 direction;
    float importance;
    glm::vec3 color;
    bool finalNode;
    bool insideObject;



    //constructor
    Ray(glm::vec3);
    //Instance methods  
    glm::vec3 calculateColor();
    glm::vec3 calculateLocalContribution();

};