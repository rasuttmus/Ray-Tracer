#include "pixel.h"

Pixel::Pixel(int n, double s, int x,  int y, glm::dvec3 c):
numberOfRays(n), pixelSize(s), pixelPosX(x), pixelPosY(y), cameraPos(c){}

void Pixel::shootingRays(int numOfRays) {
    glm::dvec3 direction;
    double randX, randY, diffX, diffY;
    glm::dvec3 initDirection;
    Ray *r;

    srand(static_cast <unsigned int> (time(0)));

    for(int i = 0; i < 1; i++) {
        
        direction.x = pixelSize * pixelPosX + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (pixelSize * (pixelPosX + 1) - pixelSize * pixelPosX)));
        direction.y = pixelSize * pixelPosY + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (pixelSize * (pixelPosY + 1) - pixelSize * pixelPosY)));
        
        direction.z = 1.0;

        initDirection.x = direction.x - cameraPos.x;
        initDirection.y = direction.y - cameraPos.y;

        glm::dvec3 tmpDir = glm::dvec3(0.0, 0.0, 1.0);
        glm::dvec3 tmpPos = glm::dvec3(0.3, 0.5, -0.5);

        r = new Ray(glm::normalize(tmpDir), tmpPos);
        r->setImportance(1 / numberOfRays);
        addRay(r);
        //addRay(new Ray(glm::normalize(initDirection), cameraPos));

        std::cout << std::endl << "Ray direction: " << "x:" << tmpDir.x << "   y:" << tmpDir.y << "   z:" << tmpDir.z << std::endl;
    }
    
    //int counter = 0;
    int type;
    int counter = 0;
    int id = 0;

    glm::dvec3 intersectionPoint = glm::dvec3(-2.0, -2.0, 2.0);
    glm::dvec3 intersectionNormal(0.0, 0.0, 0.0);

    

    for(std::vector<Ray *>::iterator rayIt = rays.begin(); rayIt != rays.end(); ++rayIt){
        intersectionPoint = glm::dvec3(-2.0, -2.0, 2.0);
        for(std::vector<Shape *>::iterator shapeIt = shapes.begin(); shapeIt != shapes.end(); ++shapeIt){

            // if distance from this collision is the shortest so far, then use it instead
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            //std::cout << std::endl << "intersection: " << "(" << intersectionPoint.x << "," << intersectionPoint.y << "," << intersectionPoint.z << ")" <<std::endl;
            //std::cout << std::endl << "starting point: " << "(" << (*rayIt)->getStartingPoint().x << "," << (*rayIt)->getStartingPoint().y << "," << (*rayIt)->getStartingPoint().z << ")" <<std::endl;
            std::cout << std::endl << "lengthSTD: " << glm::length(glm::dvec3(-2.0, -2.0, 2.0) - (*rayIt)->getStartingPoint()) << std::endl;
            

            if(glm::length(intersectionPoint - (*rayIt)->getStartingPoint()) > glm::length((*shapeIt)->calculateIntersections((*rayIt)->getDirection(), (*rayIt)->getStartingPoint()) - (*rayIt)->getStartingPoint())){
                intersectionPoint = (*shapeIt)->calculateIntersections((*rayIt)->getDirection(), (*rayIt)->getStartingPoint());
                std::cout << std::endl << "lengthNEW: " << glm::length(intersectionPoint - (*rayIt)->getStartingPoint()) << std::endl;
                //intersectionNormal = (*shapeIt)->getIntersectionNormal();
                type = (*shapeIt)->getType();
                id = counter;
            }
            counter++;
        }
        
        std::cout << std::endl << "Hit!" << "   x: " << intersectionPoint.x << "   y: " << intersectionPoint.y << "   z: " << intersectionPoint.z << std::endl;
        
        counter = 0;
        std::cout <<"num: 0" << std::endl;
        //std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

        std::cout << std::endl << "type: " << type << std::endl;
       
        if(type != 2){
            shapes.at(id)->computeChildrenRays((*rayIt));
            std::cout << std::endl << "id: " << id << std::endl;
            std::cout << std::endl << "startpos reflection: " << "(" << (*rayIt)->reflectionRay->getStartingPoint().x << ", " << (*rayIt)->reflectionRay->getStartingPoint().y << ", " << (*rayIt)->reflectionRay->getStartingPoint().z << ")" << std::endl;
            std::cout << std::endl << "reflection direction: " << "(" << (*rayIt)->reflectionRay->getDirection().x << ", " << (*rayIt)->reflectionRay->getDirection().y << ", " << (*rayIt)->reflectionRay->getDirection().z << ")" << std::endl;

            if((*rayIt)->reflectionRay != NULL && (*rayIt)->refractionRay != NULL){
                //RÄKNA NÅNTING
                shootChildrenRays((*rayIt)->reflectionRay, 1);
                shootChildrenRays((*rayIt)->refractionRay, 1);
            }
            else if((*rayIt)->reflectionRay != NULL){
                (*rayIt)->reflectionRay->setImportance((*rayIt)->getImportance());
                shootChildrenRays((*rayIt)->reflectionRay, 1);
            }
        }
        
        if(type == 2)
            (*rayIt)->setFinalNode(true);
    }
}

void Pixel::shootChildrenRays(Ray *r, int numOfChildren) {
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
    std::cout << "num: " << numOfChildren << std::endl;
    numOfChildren++;
    int index = 0;
    int counter = 0;
    int type;
    
    glm::dvec3 intersectionPoint(-2.0, -2.0, 2.0);

    for(std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); ++it){
        if(glm::length(intersectionPoint - r->getStartingPoint()) > glm::length((*it)->calculateIntersections(r->getDirection(), r->getStartingPoint()) - r->getStartingPoint())){
            intersectionPoint = (*it)->calculateIntersections(r->getDirection(), r->getStartingPoint());
            type = (*it)->getType();
            index = counter;
        }
        counter++;
    }
    std::cout << std::endl << "Hit!" << "x: " << intersectionPoint.x << "   y: " << intersectionPoint.y << "   z: " << intersectionPoint.z << std::endl;
    if(type != 2 && intersectionPoint.x != -2){
        std::cout << std::endl << "id: " << index << std::endl;
        shapes.at(index)->computeChildrenRays(r);
        std::cout << std::endl << "startpos reflection: " << "(" << r->reflectionRay->getStartingPoint().x << ", " << r->reflectionRay->getStartingPoint().y << ", " << r->reflectionRay->getStartingPoint().z << ")" << std::endl;
        std::cout << std::endl << "reflection direction: " << "(" << r->reflectionRay->getDirection().x << ", " << r->reflectionRay->getDirection().y << ", " << r->reflectionRay->getDirection().z << ")" << std::endl;
    }

    std::cout << std::endl << "       type: " << type << std::endl;
    
    if(numOfChildren < 10 && type != 2 && intersectionPoint.x != -2){

        shootChildrenRays(r->reflectionRay, numOfChildren);
        if(r->refractionRay != NULL){
            shootChildrenRays(r->refractionRay, numOfChildren);
        }
    }
    if(type == 2 || numOfChildren == 9)
            (r)->setFinalNode(true);
}

void Pixel::addRay(Ray *r){
    rays.push_back(r);
}

int Pixel::getNumberOfRays(){
    return numberOfRays;
}
