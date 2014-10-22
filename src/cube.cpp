#include "cube.h"

Cube::Cube(glm::vec3 p, float s, bool t, float ref): 
position(p), size(s), transparent(t), refractiveIndex(ref){
    initRectangleObjects();
}

void Cube::initRectangleObjects(){
    addRectangle(new Rectangle(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    addRectangle(new Rectangle(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    addRectangle(new Rectangle(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    addRectangle(new Rectangle(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f)));
    
    for(std::vector<Rectangle *>::iterator it = rectangles.begin(); it != rectangles.end(); ++it){
        for(std::vector<glm::vec3>::iterator it2 = (*it)->corners.begin(); it2 != (*it)->corners.end(); ++it2){
            (*it2).x = ((*it2).x * size) + position.x;
            (*it2).y = ((*it2).y * size) + position.y;
            (*it2).z = ((*it2).z * size) + position.z;
        }
    }
}

glm::vec3 Cube::calculateIntersections(Ray *ray){
    glm::vec3 intersection;
    for(std::vector<Rectangle *>::iterator it = rectangles.begin(); it != rectangles.end(); ++it)
        intersection = (*it)->calculateIntersections(ray);

     return intersection;
}
void Cube::computeChildrenRays(Ray *ray, glm::vec3 intersection){
        
    glm::vec3 instersectionPoint;

    for(std::vector<Rectangle *>::iterator it = rectangles.begin(); it != rectangles.end(); ++it){
        instersectionPoint = (*it)->calculateIntersections(ray->getDirection(), ray->getStartingPoint());
        std::cout << std::endl << "  instersectionPoint: " << "(" << instersectionPoint.x << ", " << instersectionPoint.y << "," << instersectionPoint.z << ")" << std::endl << std::endl;
    }
}

void Cube::addRectangle(Rectangle *r){
    rectangles.push_back(r);
}

void Cube::setPosition(glm::vec3 p){
    position = p;
}

glm::vec3 Cube::getPosition(){
    return position;
}

int Cube::getType(){
    return CUBE_SHAPE;
}