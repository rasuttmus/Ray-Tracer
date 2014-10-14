#include "glm/glm.hpp"

class Ray{
public:
    //Instance variables
    glm::vec3 startingPoint;
    glm::vec3 direction;
    float importance;
    glm::vec3 color;
    bool finalNode;
    //var *childrenNodes;
    bool insideObject;


    //constructor
    Ray();
    //Instance methods  
    glm::vec3 calculateColor();
    glm::vec3 calculateLocalContribution();

};