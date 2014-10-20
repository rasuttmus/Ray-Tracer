#include "pixel.h"

Pixel::Pixel(int n, float s, int x,  int y, glm::vec3 c): 
pixelSize(s), pixelPosX(x), pixelPosY(y), cameraPos(c)
{
    shootingRays(n);
}

void Pixel::shootingRays(int numOfRays) {
    glm::vec3 direction;
    float randX, randY, diffX, diffY;
    glm::vec3 initDirection;
    srand(static_cast <unsigned int> (time(0)));

    for(int i = 0; i < numOfRays; i++) {
        randX = ((float) rand()) / RAND_MAX;
        diffX = pixelSize*(pixelPosX+1) - pixelPosX*pixelSize;
        direction.x = pixelPosX*pixelSize + (randX * diffX);

        randY = ((float) rand()) / RAND_MAX;
        diffY = pixelSize*(pixelPosY+1) - pixelPosY*pixelSize;
        direction.y = pixelPosY*pixelSize + (randY * diffY);

        direction.z = 1.0f;

        initDirection = glm::normalize(direction - cameraPos);

        //Ray *startingRay = new Ray(direction);

        /**********   Might be wrong!!! ************/
        //startingRay->setStartingPoint(cameraPos);
        

/*  RITADE MED KOD 
        Ray *ray = new Ray(direction);


        ray->reflectionRay = new Ray(direction);

        rays.push_back(ray);
        */


    }
}
