#include "cube.h"

Cube::Cube(glm::vec3 p, float s, bool t, float ref): 
position(p), size(s), transparent(t), refractiveIndex(ref){
    initRectangleObjects();
}

void Cube::initRectangleObjects(){
    addRectangle(new Rectangle(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, -1.0f)));
    addRectangle(new Rectangle(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    
    for(std::vector<Rectangle *>::iterator it = rectangles.begin(); it != rectangles.end(); ++it){
        for(std::vector<glm::vec3>::iterator it2 = (*it)->corners.begin(); it2 != (*it)->corners.end(); ++it2){
            (*it2).x = ((*it2).x * size) + position.x;
            (*it2).y = ((*it2).y * size) + position.y;
            (*it2).z = ((*it2).z * size) - position.z;
            std::cout << std::endl << "   cornerPos: " << "x: " << (*it2).x << "   y: " << (*it2).y << "   z: " << (*it2).z << std::endl;
        }
    }

    Ray *ray = new Ray(glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(0.70f, 0.70f, -2.0f));
    //ray->setStartingPoint(glm::vec3(0.70f, 0.70f, -2.0f));
}

void Cube::computeChildrenRays(Ray *ray){
    for(std::vector<Rectangle *>::iterator it = rectangles.begin(); it != rectangles.end(); ++it){
        (*it)->calculateIntersections(ray);
    }
}

void Cube::addRectangle(Rectangle *r){
    rectangles.push_back(r);
}