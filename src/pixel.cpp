#include "pixel.h"

Pixel::Pixel(int n, double s, int x,  int y, glm::dvec3 c):
numberOfRays(n), pixelSize(s), pixelPosX(x), pixelPosY(y), cameraPos(c){}

void Pixel::shootingRays(int numOfRays) {
    glm::dvec3 direction;
    double randX, randY, diffX, diffY;
    glm::dvec3 initDirection;
    Ray *r;

    srand(static_cast <unsigned int> (time(0)));

    for(int i = 0; i < numOfRays; i++) {
        
        direction.x = pixelSize * pixelPosX + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (pixelSize * (pixelPosX + 1) - pixelSize * pixelPosX)));
        direction.y = pixelSize * pixelPosY + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (pixelSize * (pixelPosY + 1) - pixelSize * pixelPosY)));
        
        direction.z = 1.0;

        glm::dvec3 tmpDir = glm::dvec3(0.0, 0.0, 1.0);
        glm::dvec3 tmpPos = glm::dvec3(0.3, 0.5, -0.5);

        r = new Ray(glm::normalize(direction), cameraPos);
        r->setImportance(1 / numberOfRays);
        addRay(r);
        //addRay(new Ray(glm::normalize(initDirection), cameraPos));
        //sätt ray importance

        //std::cout << std::endl << "Ray direction: " << "x:" << tmpDir.x << "   y:" << tmpDir.y << "   z:" << tmpDir.z << std::endl;
    }
    
    //int counter = 0;
    int type;
    int counter = 0;
    int id = 0;

    glm::dvec3 intersectionPoint = glm::dvec3(-2.0, -2.0, 2.0);
    glm::dvec3 intersectionNormal(0.0, 0.0, 0.0);
    int wallIntersectionIndex = 0;

    

    for(std::vector<Ray *>::iterator rayIt = rays.begin(); rayIt != rays.end(); ++rayIt){
        intersectionPoint = glm::dvec3(-2.0, -2.0, 2.0);
        for(std::vector<Shape *>::iterator shapeIt = shapes.begin(); shapeIt != shapes.end(); ++shapeIt){

            // if distance from this collision is the shortest so far, then use it instead
            //std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            //std::cout << std::endl << "intersection: " << "(" << intersectionPoint.x << "," << intersectionPoint.y << "," << intersectionPoint.z << ")" <<std::endl;
            //std::cout << std::endl << "starting point: " << "(" << (*rayIt)->getStartingPoint().x << "," << (*rayIt)->getStartingPoint().y << "," << (*rayIt)->getStartingPoint().z << ")" <<std::endl;
            //std::cout << std::endl << "lengthSTD: " << glm::length(glm::dvec3(-2.0, -2.0, 2.0) - (*rayIt)->getStartingPoint()) << std::endl;
            

            if(glm::length(intersectionPoint - (*rayIt)->getStartingPoint()) > glm::length((*shapeIt)->calculateIntersections((*rayIt)->getDirection(), (*rayIt)->getStartingPoint()) - (*rayIt)->getStartingPoint())){
                intersectionPoint = (*shapeIt)->calculateIntersections((*rayIt)->getDirection(), (*rayIt)->getStartingPoint());
                //std::cout << std::endl << "lengthNEW: " << glm::length(intersectionPoint - (*rayIt)->getStartingPoint()) << std::endl;
                type = (*shapeIt)->getType();
                id = counter;
                if(type != 1 || type != 3)
                    wallIntersectionIndex = (*shapeIt)->getWallIntersectionIndex();
            }
            counter++;
        }
        (*rayIt)->setIntersectionPoint(intersectionPoint);
        (*rayIt)->setIntersectionType(type);
        (*rayIt)->setIntersectionNormal(shapes.at(id)->getIntersectionNormal());

        glm::dvec3 shadowRay = (*rayIt)->calculateShadowRay(intersectionPoint, shapes.at(0)->randomPosition());
        glm::dvec3 shadowRayIntersection(-2.0, -2.0, 2.0);
        int shadowRayType = 0;
        //std::cout << std::endl << "shadowRayDir: (" << glm::normalize(shadowRay).x << ", " << glm::normalize(shadowRay).y << ", " << glm::normalize(shadowRay).z << ")" << std::endl;

        for(std::vector<Shape *>::iterator shapeIt = shapes.begin(); shapeIt != shapes.end(); ++shapeIt){
            if(glm::length(shadowRayIntersection - intersectionPoint) > glm::length((*shapeIt)->calculateIntersections(glm::normalize(shadowRay), intersectionPoint) - intersectionPoint)){
                shadowRayIntersection = (*shapeIt)->calculateIntersections(glm::normalize(shadowRay), intersectionPoint);
                shadowRayType = (*shapeIt)->getType();
            }
        }

        /*if(shadowRayType == 3)
            (*rayIt)->setColor(shapes.at(id)->getColor(wallIntersectionIndex));
        else
            (*rayIt)->setColor(shapes.at(id)->getColor(wallIntersectionIndex)*0.1);

        if((int)round(intersectionPoint.x) == -2)
            (*rayIt)->setColor(glm::dvec3(0.0, 0.0, 0.0));

        if(type == 3)
            (*rayIt)->setColor(shapes.at(id)->getColor(wallIntersectionIndex));
*/
        
        counter = 0;
        
       
        if(type != 2 || type != 3){
            shapes.at(id)->computeChildrenRays((*rayIt));
            (*rayIt)->calculateImportance(shapes.at(id)->getRefractiveIndex());
            //std::cout << std::endl << "id: " << id << std::endl;
            //std::cout << std::endl << "startpos reflection: " << "(" << (*rayIt)->reflectionRay->getStartingPoint().x << ", " << (*rayIt)->reflectionRay->getStartingPoint().y << ", " << (*rayIt)->reflectionRay->getStartingPoint().z << ")" << std::endl;
            //std::cout << std::endl << "reflection direction: " << "(" << (*rayIt)->reflectionRay->getDirection().x << ", " << (*rayIt)->reflectionRay->getDirection().y << ", " << (*rayIt)->reflectionRay->getDirection().z << ")" << std::endl;

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
        
        if(type == 2 || type == 3 || (*rayIt)->reflectionRay == NULL){
            (*rayIt)->setFinalNode(true);
            (*rayIt)->setColor(shapes.at(id)->getColor(wallIntersectionIndex));
        }

        //Here we must calculate the intersections contribution to the image
        (*rayIt)->setColor(glm::dvec3(0.0, 0.0, 0.0));
        (*rayIt)->setColor(shapes.at(id)->getColor(wallIntersectionIndex));
        //debug

        if(type != 3 && shadowRayType == 3)
            (*rayIt)->setColor((*rayIt)->calculateColor(shapes.at(0)->randomPosition()));

        if(shadowRayType != 3)
            (*rayIt)->setColor(shapes.at(id)->getColor(wallIntersectionIndex)*0.2);

        /*if((int)intersectionPoint.x == -2){
            (*rayIt)->setColor(glm::dvec3(0.0, 0.0, 0.0));
        }*/
        //debug
        colorOfPixel += (*rayIt)->getColor();
    }
    colorOfPixel /= numOfRays;
}

void Pixel::shootChildrenRays(Ray *r, int numOfChildren) {

    numOfChildren++;
    int index = 0;
    int counter = 0;
    int wallIntersectionIndex = 0;
    int type;
    
    glm::dvec3 intersectionPoint(-2.0, -2.0, 2.0);

    for(std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); ++it){
        if(glm::length(intersectionPoint - r->getStartingPoint()) > glm::length((*it)->calculateIntersections(r->getDirection(), r->getStartingPoint()) - r->getStartingPoint())){
            intersectionPoint = (*it)->calculateIntersections(r->getDirection(), r->getStartingPoint());
            type = (*it)->getType();
            index = counter;
            if(type != 1 || type != 3)
                wallIntersectionIndex = (*it)->getWallIntersectionIndex();
        }
        counter++;
    }
    
    if(type != 2 && type != 3 && (int)round(intersectionPoint.x) != -2){
        shapes.at(index)->computeChildrenRays(r);
        r->calculateImportance(shapes.at(index)->getRefractiveIndex());
    }
    
    if(numOfChildren < 10 && type != 2 && type != 3 && (int)round(intersectionPoint.x) != -2){
        r->reflectionRay->setImportance(r->getImportance());
        shootChildrenRays(r->reflectionRay, numOfChildren);
        if(r->refractionRay != NULL){
            shootChildrenRays(r->refractionRay, numOfChildren);
        }
    }
    if(type == 2 || numOfChildren == 9 || type == 3 || r->reflectionRay == NULL || (int)round(intersectionPoint.x) == -2){
        (r)->setFinalNode(true);
        (r)->setColor(shapes.at(index)->getColor(wallIntersectionIndex));
    }
}

void Pixel::addRay(Ray *r){
    rays.push_back(r);
}

int Pixel::getNumberOfRays(){
    return numberOfRays;
}

void Pixel::setColorOfPixel(glm::dvec3 c){
    colorOfPixel = c;
}

glm::dvec3 Pixel::getColorOfPixel(){
    return colorOfPixel;
}
