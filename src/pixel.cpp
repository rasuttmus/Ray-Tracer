#include "pixel.h"

Pixel::Pixel(int n, float s, int x,  int y, glm::vec3 c):
numberOfRays(n), pixelSize(s), pixelPosX(x), pixelPosY(y), cameraPos(c){}

void Pixel::shootingRays(int numOfRays) {
    glm::vec3 direction;
    float randX, randY, diffX, diffY;
    glm::vec3 initDirection;
    srand(static_cast <unsigned int> (time(0)));

    /*** DETTA KAN VARA FEL ***/

    for(int i = 0; i < numOfRays; i++) {
        
        direction.x = pixelSize * pixelPosX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (pixelSize * (pixelPosX + 1) - pixelSize * pixelPosX)));
        direction.y = pixelSize * pixelPosY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (pixelSize * (pixelPosY + 1) - pixelSize * pixelPosY)));
        
        direction.z = 1.0f;

        initDirection = glm::normalize(direction - cameraPos);

        addRay(new Ray(initDirection, cameraPos));

        std::cout << std::endl << "init direction: " << "x:" << initDirection.x << "   y:" << initDirection.y << "   z:" << initDirection.z << std::endl;
    }
    glm::vec3 intersection(10000.0f, 10000.0f, 10000.0f);
    glm::vec3 distance(100.0f, 100.0f, 100.0f);
    int counter = 0;
    int type;
    int id;
    for(std::vector<Ray *>::iterator rayIt = rays.begin(); rayIt != rays.end(); ++rayIt){
        for(std::vector<Shape *>::iterator shapeIt = shapes.begin(); shapeIt != shapes.end(); ++shapeIt){

            // THIS IS A CUBE
            if((*shapeIt)->getType() == 0) {
                // if distance from this collision is the shortest so far, then use it instead
                //std::cout << std::endl << "length: " << glm::length(intersection - ((*rayIt)->getStartingPoint())) << std::endl;
                //std::cout << std::endl << "length2: " << glm::length((*shapeIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint()) << std::endl;
                if(glm::length((*shapeIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint()) <= glm::length(intersection - ((*rayIt)->getStartingPoint()))){
                    if((*shapeIt)->calculateIntersections((*rayIt)).x < 10000.0f){
                        distance = (*shapeIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint();
                        intersection = (*shapeIt)->calculateIntersections((*rayIt));
                        type = (*shapeIt)->getType();
                        id = counter;
                        std::cout << std::endl << "intersection: " << "x: " << intersection.x << "  y: " << intersection.y << "  z: " << intersection.z << std::endl;
                        std::cout << std::endl << "counter: " << counter << " Cube" << std::endl;
                    }
                }
            } 
            // THIS IS A SPHERE
            else if((*shapeIt)->getType() == 1){
                // if distance from this collision is the shortest so far, then use it instead
                if(glm::length((*shapeIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint()) <= glm::length(intersection - ((*rayIt)->getStartingPoint()))){
                    if((*shapeIt)->calculateIntersections((*rayIt)).x < 10000.0f){
                        distance = (*shapeIt)->calculateIntersections((*rayIt)) - (*rayIt)->getStartingPoint();
                        intersection = (*shapeIt)->calculateIntersections((*rayIt));
                        type = (*shapeIt)->getType();
                        id = counter;
                        std::cout << std::endl << "intersection: " << "x: " << intersection.x << "  y: " << intersection.y << "  z: " << intersection.z << std::endl;
                        std::cout << std::endl << "counter: " << counter << " Sphere" << std::endl;
                    }
                }
            }
            counter++;
            
        }
        if((*rayIt)->getIntersected() && type == 0){
            shapes.at(id)->computeChildrenRays((*rayIt), intersection);
        } 
        else if((*rayIt)->getIntersected() && type == 1){
            shapes.at(id)->computeChildrenRays((*rayIt), intersection);
        }
        counter = 0;
    }
/*
    glm::vec3 cubePos;
    glm::vec3 spherePos;
    glm::vec3 dist;

    for(std::vector<Ray *>::iterator rayIt = rays.begin(); rayIt != rays.end(); ++rayIt)
        for(std::vector<Cube *>::iterator cubeIt = cubes.begin(); cubeIt != cubes.end(); ++cubeIt){       
                cubePos = (*cubeIt)->getPosition();
                //spherePos = (*sphereIt)->getPosition();

                if(glm::length(cubePos - cameraPos) <= glm::length(spherePos - cameraPos))
                    (*cubeIt)->computeChildrenRays((*rayIt));
                else
                    (*sphereIt)->computeChildrenRays((*rayIt));
        }
        for(std::vector<Sphere *>::iterator sphereIt = spheres.begin(); sphereIt != spheres.end(); ++sphereIt){ 
        }
    }
*/
    

    /*for(std::vector<Ray *>::iterator it = rays.begin(); it != rays.end(); ++it){
        (*it)
    }*/


}

void Pixel::addRay(Ray *r){
    rays.push_back(r);
}

int Pixel::getNumberOfRays(){
    return numberOfRays;
}
