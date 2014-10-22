#include "pixel.h"

Pixel::Pixel(int n, float s, int x,  int y, glm::vec3 c):
numberOfRays(n), pixelSize(s), pixelPosX(x), pixelPosY(y), cameraPos(c){}

void Pixel::shootingRays(int numOfRays) {
    glm::vec3 direction;
    float randX, randY, diffX, diffY;
    glm::vec3 initDirection;
    srand(static_cast <unsigned int> (time(0)));

    for(int i = 0; i < numOfRays; i++) {
        
        direction.x = pixelSize * pixelPosX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (pixelSize * (pixelPosX + 1) - pixelSize * pixelPosX)));
        direction.y = pixelSize * pixelPosY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (pixelSize * (pixelPosY + 1) - pixelSize * pixelPosY)));
        
        direction.z = 1.0f;

        initDirection = glm::normalize(direction - cameraPos);

        addRay(new Ray(initDirection, cameraPos));

        std::cout << std::endl << "init direction: " << "x:" << initDirection.x << "   y:" << initDirection.y << "   z:" << initDirection.z << std::endl;
    }
    
    //int counter = 0;
    int type;
    int counter = 0;
    int id = 0;

    glm::vec3 intersectionPoint(-2.0f, -2.0f, 2.0f);
    glm::vec3 intersectionNormal(0.0f, 0.0f, 0.0f);

    for(std::vector<Ray *>::iterator rayIt = rays.begin(); rayIt != rays.end(); ++rayIt){
        for(std::vector<Shape *>::iterator shapeIt = shapes.begin(); shapeIt != shapes.end(); ++shapeIt){

            // THIS IS A CUBE
            if((*shapeIt)->getType() == 0) {
                // if distance from this collision is the shortest so far, then use it instead
                //std::cout << std::endl << "length: " << glm::length(intersection - ((*rayIt)->getStartingPoint())) << std::endl;
                //std::cout << std::endl << "length2: " << glm::length((*shapeIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint()) << std::endl;
                
                if(glm::length(intersectionPoint - (*rayIt)->getStartingPoint()) > glm::length((*shapeIt)->calculateIntersections((*rayIt)->getDirection(), (*rayIt)->getStartingPoint()) - (*rayIt)->getStartingPoint())){
                    intersectionPoint = (*shapeIt)->calculateIntersections((*rayIt)->getDirection(), (*rayIt)->getStartingPoint());
                    //intersectionNormal = (*shapeIt)->getIntersectionNormal();
                    id = counter;
                }
            }
            // THIS IS A SPHERE
            else if((*shapeIt)->getType() == 1){
                // if distance from this collision is the shortest so far, then use it instead
                if(glm::length(intersectionPoint - (*rayIt)->getStartingPoint()) > glm::length((*shapeIt)->calculateIntersections((*rayIt)->getDirection(), (*rayIt)->getStartingPoint()) - (*rayIt)->getStartingPoint())){
                    intersectionPoint = (*shapeIt)->calculateIntersections((*rayIt)->getDirection(), (*rayIt)->getStartingPoint());
                    id = counter;
                    //intersectionNormal = (*shapeIt)->getIntersectionNormal();
                }
            }
            counter++;
        }
        counter = 0;
    }
}

void Pixel::addRay(Ray *r){
    rays.push_back(r);
}

int Pixel::getNumberOfRays(){
    return numberOfRays;
}
