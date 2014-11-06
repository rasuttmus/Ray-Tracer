#include "pixel.h"

Pixel::Pixel(int n, double s, int x,  int y, glm::dvec3 c):
numberOfRays(n), pixelSize(s), pixelPosX(x), pixelPosY(y), cameraPos(c){}

void Pixel::shootingRays(int numOfRays) {
    glm::dvec3 direction;
    double randX, randY, diffX, diffY;
    glm::dvec3 initDirection;
    Ray *r;

    srand(static_cast <unsigned int> (time(0)));

    //Loop to create a set of rays that will contribute to the pixel
    for(int i = 0; i < numOfRays; i++) {
        
        //Random direction for each ray in the pixel
        direction.x = pixelSize * pixelPosX + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (pixelSize * (pixelPosX + 1) - pixelSize * pixelPosX)));
        direction.y = pixelSize * pixelPosY + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (pixelSize * (pixelPosY + 1) - pixelSize * pixelPosY)));
        
        direction.z = 1.0;

        glm::dvec3 tmpDir = glm::dvec3(0.0, 0.0, 1.0);
        glm::dvec3 tmpPos = glm::dvec3(0.51, 0.5, -2.0);

        //Create the rays and adds them to a vector  
        r = new Ray(glm::normalize(direction), cameraPos);
        r->setImportance(5.0 / numberOfRays);
        addRay(r);
    
    }
    
   //Set initial values for variables
    int type;
    int counter = 0;
    int id = 0;
    glm::dvec3 intersectionPoint = glm::dvec3(-2.0, -2.0, 2.0);
    glm::dvec3 intersectionNormal(0.0, 0.0, 0.0);
    int wallIntersectionIndex = 0;

    
    //Loop that goes through the vector of initially created rays
    for(std::vector<Ray *>::iterator rayIt = rays.begin(); rayIt != rays.end(); ++rayIt){
        intersectionPoint = glm::dvec3(-2.0, -2.0, 2.0);

        //Loop that goes through all shapes in the scene and checks intersections
        for(std::vector<Shape *>::iterator shapeIt = shapes.begin(); shapeIt != shapes.end(); ++shapeIt){

            // if the distance to this collision is the shortest so far, then use it instead
            if(glm::length(intersectionPoint - (*rayIt)->getStartingPoint()) > glm::length((*shapeIt)->calculateIntersections(*rayIt) - (*rayIt)->getStartingPoint())){
                intersectionPoint = (*shapeIt)->calculateIntersections(*rayIt);
                type = (*shapeIt)->getType();
                id = counter;
                //Get rectangle index if the intersected object is cube or room
                if(type == 0 || type == 2)
                    wallIntersectionIndex = (*shapeIt)->getWallIntersectionIndex();
            }
            counter++;
        }

        (*rayIt)->setIntersectionPoint(intersectionPoint);
        (*rayIt)->setIntersectionType(type);
        (*rayIt)->setIntersectionNormal(shapes.at(id)->getIntersectionNormal());

        //Create shadowray
        Ray *shadowRay = new Ray(glm::normalize((*rayIt)->calculateShadowRay(intersectionPoint, shapes.at(0)->randomPosition())), intersectionPoint);
        glm::dvec3 shadowRayIntersection(-2.0, -2.0, 2.0);
        int shadowRayType = 0;
        
        //Loop through all shapes and check if the shadowrays intersects with any opaque object
        for(std::vector<Shape *>::iterator shapeIt = shapes.begin(); shapeIt != shapes.end(); ++shapeIt){
            if(glm::length(shadowRayIntersection - intersectionPoint) > glm::length((*shapeIt)->calculateIntersections(shadowRay) - intersectionPoint) && !(*shapeIt)->getTransparency()){
                shadowRayIntersection = (*shapeIt)->calculateIntersections(shadowRay);
                shadowRayType = (*shapeIt)->getType();
            }
        }
         
         //if intersectionpoint is not in the scene set color to black       
        if((int)round(intersectionPoint.x) == -2)
            (*rayIt)->setColor(glm::dvec3(0.0, 0.0, 0.0));
                
        counter = 0;
        //Set the initial color to black for all rays
        (*rayIt)->setColor(glm::dvec3(0.0, 0.0, 0.0));

        //Decide for which shapes children rays will be calculated (Sphere and Cube)
        if(type == 0 || type == 1){
            shapes.at(id)->computeChildrenRays((*rayIt));
            (*rayIt)->calculateImportance(shapes.at(id)->getRefractiveIndex(), shapes.at(id)->getTransparency());

            //If the intersected object is transparent it will result in a reflected and a refracted ray. Else there will only be reflection
            if(shapes.at(id)->getTransparency()){
                (*rayIt)->reflectionRay->setImportance((*rayIt)->getImportance());
                (*rayIt)->refractionRay->setImportance((*rayIt)->getImportance());
                shootChildrenRays((*rayIt)->reflectionRay, 1);
                shootChildrenRays((*rayIt)->refractionRay, 1);
            }
            else{
                (*rayIt)->reflectionRay->setImportance((*rayIt)->getImportance());
                shootChildrenRays((*rayIt)->reflectionRay, 1);
            }   
        }

        //Set the color of the ray
        (*rayIt)->setColor(shapes.at(id)->getColor(wallIntersectionIndex));
       
        //if ray hits object
        if(type == 0 || type == 1) 
            (*rayIt)->setColor((*rayIt)->calculateColor(shapes.at(0)->randomPosition(), shadowRayType));

        //if first ray hits walls
        if(type == 2){
            (*rayIt)->setFinalNode(true);
            (*rayIt)->setColor(shapes.at(id)->getColor(wallIntersectionIndex));
            (*rayIt)->setColor((*rayIt)->calculateColor(shapes.at(0)->randomPosition(), shadowRayType));
        }
        
        //if ray hits lightsource, set it to white
        if(type == 3){
            (*rayIt)->setFinalNode(true);
            (*rayIt)->setColor(glm::dvec3(1.0, 1.0, 1.0));
        }

        //Add upp the rays contribution to pixel
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


    //check what object child ray intersects with
    for(std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); ++it){
        if(glm::length(intersectionPoint - r->getStartingPoint()) > glm::length((*it)->calculateIntersections(r) - r->getStartingPoint())){
            intersectionPoint = (*it)->calculateIntersections(r);
            type = (*it)->getType();
            index = counter;
            if(type == 0 || type == 2)
                wallIntersectionIndex = (*it)->getWallIntersectionIndex();
        }
        counter++;
    }

    //Create shadowray
    Ray *shadowRay = new Ray(glm::normalize(r->calculateShadowRay(intersectionPoint, shapes.at(0)->randomPosition())), intersectionPoint);
    glm::dvec3 shadowRayIntersection(-2.0, -2.0, 2.0);
    int shadowRayType = 0;
    
    //Loop through all shapes and check if the shadowrays intersects with any object
    for(std::vector<Shape *>::iterator shapeIt = shapes.begin(); shapeIt != shapes.end(); ++shapeIt){
        if(glm::length(shadowRayIntersection - intersectionPoint) > glm::length((*shapeIt)->calculateIntersections(shadowRay) - intersectionPoint)){
            shadowRayIntersection = (*shapeIt)->calculateIntersections(shadowRay);
            shadowRayType = (*shapeIt)->getType();
        }
    }

    //If children ray hits object, compute children to them
    if(type == 1 || type == 0){
        shapes.at(index)->computeChildrenRays(r);
        r->calculateImportance(shapes.at(index)->getRefractiveIndex(), shapes.at(index)->getTransparency());

            //If its not a final node, shoot new children
            if(numOfChildren < 10 && r->reflectionRay != NULL){
                    r->reflectionRay->setImportance(r->getImportance());
                    shootChildrenRays(r->reflectionRay, numOfChildren);
                    
                    if(r->refractionRay != NULL){
                        r->refractionRay->setImportance(r->getImportance());
                        shootChildrenRays(r->refractionRay, numOfChildren);
                    }
            }   
    }

     //Set the color of the ray
        r->setColor(shapes.at(index)->getColor(wallIntersectionIndex));

    //If ray hits wall, light or has reach maximum number of children 
    if(type == 2 || type == 3 || numOfChildren == 10 || r->reflectionRay == NULL){
        r->setFinalNode(true);
        r->setColor(shapes.at(index)->getColor(wallIntersectionIndex));
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
