#include "ray.h"

Ray::Ray(glm::dvec3 d, glm::dvec3 s):
		 direction(d), startingPoint(s){
}



glm::dvec3 Ray::calculateColor(glm::dvec3 lightPos, int shadowRayType) {
    

    /* HÄR MECKAR VI!! SAKER Är BORTMARKERADE FÖR ATT TESTA ATT LOCALCONTRIBUTION ÄR FÖR HÖG OCH REFRACTED CONTRIBUTION ÄR FÖR LÅG!
    */    

    //debug
    double localContributionImportance = 1.0 - importance;

    //recursive function thats goes through all child rays. 
    if(finalNode == true){
        color = importance * color + localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay == NULL){
        color = reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->importance * color * 10.0
                 + localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay != NULL && calculateLocalContribution(lightPos, shadowRayType).x > 0.0){
        color = (reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->getImportance() * 30.0 + 
                (refractionRay->getImportance()) * refractionRay->calculateColor(lightPos, shadowRayType) * 30.0) * color
                + importance * 0.0 * calculateLocalContribution(lightPos, shadowRayType) * color;
        //std::cout << "color (" << color.x << ", " << color.y << ", " << color.z << ")" << std::endl;
        /*if(intersectionType == 1){
            color = (reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->reflectedRadiance + 
                (importance - reflectionRay->reflectedRadiance) * refractionRay->calculateColor(lightPos, shadowRayType)) * color;
         } */
    
    //debug
    }
    if(color.x < 0.0 || color.y < 0.0 || color.z < 0.0)
        color = glm::dvec3(0.0, 0.0, 0.0);

    return color;
}

glm::dvec3 Ray::calculateLocalContribution(glm::dvec3 lightPos, int shadowRayType){
    glm::dvec3 localLighting(0.0, 0.0, 0.0);
    double diffuseConstant = 1.0;
    double specularConstant = 1.3;
    double highlightConstant = 10.0;
    glm::dvec3 lightSourceColor(1.0, 1.0, 1.0);

    glm::dvec3 shadowRay = glm::normalize(lightPos - intersectionPoint);
    glm::dvec3 invShadowRay = glm::normalize(intersectionPoint - lightPos);
    glm::dvec3 shadowRayReflection = glm::normalize(invShadowRay - 2 * (glm::dot(invShadowRay, intersectionNormal)) * intersectionNormal);
    glm::dvec3 viewDirection = glm::normalize(startingPoint - intersectionPoint);

    //if shadowray does not intersect with lightsource
    /*if(shadowRayType != 3){
        return glm::dvec3(0.05, 0.05, 0.05);
    }*/

    /*if(acos(glm::dot(shadowRay, intersectionNormal)) < 3.14 / 2.0){
        //std::cout << "theta: " << acos(glm::dot(shadowRay, intersectionNormal)) << std::endl;
        return glm::dvec3(0.05, 0.05, 0.05);
    }*/

    //calculate diffuse phong shading
    if(intersectionType == 2)
        localLighting = diffuseConstant * (glm::dot(shadowRay, -intersectionNormal)) * lightSourceColor;
    else
        localLighting = diffuseConstant * (glm::dot(shadowRay, intersectionNormal)) * lightSourceColor;

    //If object is specular, add specular phong shading
    if(intersectionType == 0 || intersectionType == 1){
        localLighting += specularConstant * pow(glm::dot(shadowRayReflection, viewDirection), highlightConstant) * lightSourceColor;
    }

    if(localLighting.x < 0.0)
        return glm::dvec3(0.1, 0.1, 0.1);

    return localLighting + 0.1;
}

void Ray::calculateImportance(double refractiveIndex, bool transparent){
    double n1 = 1.0;
    double n2 = 1.0;
    double critAngle = 0;
    double theta1 = 0;
    double denuminator = 0;
    double numerator = 0;
    double Rs = 0;
    double Rp = 0;

    //std::cout << "refractiveIndex: " << refractiveIndex << std::endl;
    if(insideObject){
        n1 = refractiveIndex;
        critAngle = asin(n2/n1);
        //theta1 = acos(glm::normalize(glm::cross(intersectionNormal, direction)), glm::dot(intersectionNormal, direction));
        //theta1 = acos(glm::dot(direction, intersectionNormal) / (glm::length(direction) * glm::length(intersectionNormal)));
        //std::cout << std::endl << "theta1: " << theta1 << std::endl;
    }
    else 
        n2 = refractiveIndex;
    

    /*if(refractionRay == NULL && reflectionRay != NULL){
        reflectionRay->reflectedRadiance = importance;
    }
    
    if(reflectionRay != NULL && refractionRay != NULL && !finalNode && transparent == true){
        reflectionRay->reflectedRadiance = pow((n1 - n2) / (n1 + n2), 2) * importance;
        refractionRay->transmittedRadiance =  importance - reflectionRay->importance;
    }
    if(reflectionRay == NULL && refractionRay == NULL){
        reflectedRadiance = importance;
        transmittedRadiance = importance - reflectedRadiance;
    }*/

    if(refractionRay == NULL && reflectionRay != NULL){
        reflectionRay->setImportance(importance);
    }
    
    if(reflectionRay != NULL && refractionRay != NULL && !finalNode && transparent == true){
        /*if(theta1 >= critAngle){
            reflectionRay->importance = importance;
            refractionRay->importance = 0;
        } else {*/
            /*std::cout << std::endl << "importance: " << importance << std::endl;
            reflectionRay->importance = pow((n1 - n2) / (n1 + n2), 2);
            std::cout << "relected importance: " << reflectionRay->importance << std::endl;
            refractionRay->importance = importance - reflectionRay->importance;
            std::cout << "refracted importance: " << refractionRay->importance << std::endl;*/
        //}
            //std::cout << "importance: " << importance << std::endl;

            //theta1 = acos(glm::dot(intersectionNormal, -direction));
            theta1 = acos(glm::dot(-intersectionNormal, direction));
            if(theta1 > 3.14159265358979323846 / 2)
                theta1 = theta1 - 3.14159265358979323846;

            //std::cout << "normal: (" << intersectionNormal.x << ", " << intersectionNormal.y << ", " << intersectionNormal.z << ")" << std::endl;
            //std::cout << "direction: (" << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;
            //std::cout << "dot: " << glm::dot(intersectionNormal, direction) << std::endl;

            /*numerator = n1 * cos(theta1) - n2 * std::abs(1.0 - pow((n1 / n2) * sin(theta1), 2));
            denuminator = n1 * cos(theta1) + n2 * std::abs(1.0 - pow((n1 / n2) * sin(theta1), 2));

            Rs = pow(numerator / denuminator, 2);

            numerator = n1 * std::abs(1.0 - pow((n1 / n2) * sin(theta1), 2) - n2 * cos(theta1));
            denuminator = n1 * std::abs(1.0 - pow((n1 / n2) * sin(theta1), 2) + n2 * cos(theta1));

            Rp = pow(numerator / denuminator, 2);*/

            //std::cout << "theta1: " << theta1 * 180.0 / 3.14159265358979323846 << std::endl;

            //std::cout << "täljare: " << numerator << std::endl;
            //std::cout << "nämnare: " << denuminator << std::endl;

            //refractionRay->importance = Rs * importance;
            //std::cout << "importance: " << importance << std::endl;
            reflectionRay->setImportance(pow((n1 - n2) / (n1 + n2), 2) * importance);

            //std::cout << "reflected importance: " << reflectionRay->importance << std::endl;
            refractionRay->setImportance(importance - reflectionRay->getImportance());
            //std::cout << "refracted importance: " << refractionRay->importance << std::endl << std::endl;
    }
    //std::cout << "finalNode: " << finalNode << std::endl;
    if(reflectionRay == NULL && refractionRay == NULL){
        //reflectionRay->importance = 0;
        //refractionRay->importance = 0;
    }
}

glm::dvec3 Ray::calculateShadowRay(glm::dvec3 intersectionPoint, glm::dvec3 lightPos){
    return lightPos - intersectionPoint;
}

void Ray::setStartingPoint(glm::dvec3 s){
    startingPoint = s;
}

glm::dvec3 Ray::getStartingPoint(){
    return startingPoint;
}

void Ray::setDirection(glm::dvec3 d){
    direction = d;
}

glm::dvec3 Ray::getDirection(){
    return direction;
}

void Ray::setInsideObject(bool i){
    insideObject = i;
}

bool Ray::getInsideObject(){
    return insideObject;
}

void Ray::setIntersected(bool i){
    intersected = i;
}

bool Ray::getIntersected(){
    return intersected;
}

void Ray::setFinalNode(bool f){
    finalNode = f;
}

bool Ray::getFinalNode(){
    return finalNode;
}

void Ray::setImportance(double i){
    importance = i;
}

double Ray::getImportance(){
    return importance;
}

void Ray::setColor(glm::dvec3 c){
    color = c;
}

glm::dvec3 Ray::getColor(){
    return color;
}

void Ray::setIntersectionPoint(glm::dvec3 i){
    intersectionPoint = i;
}

glm::dvec3 Ray::getIntersectionPoint(){
    return intersectionPoint;
}

void Ray::setIntersectionType(int t){
    intersectionType = t;
}

int Ray::getIntersectionType(){
    return intersectionType;
}

void Ray::setIntersectionNormal(glm::dvec3 n){
    intersectionNormal = n;
}

