#include "ray.h"

Ray::Ray(glm::dvec3 d, glm::dvec3 s):
		 direction(d), startingPoint(s){
}

glm::dvec3 Ray::calculateColor(glm::dvec3 lightPos, int shadowRayType) {
    
    double localContributionImportance = 1.0 - importance;

//recursive function thats goes through all child rays. 
//color = glm::dvec3(0.0, 0.0, 0.0);
    if(finalNode == true){
        color = localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) + importance * color;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay == NULL){
        color = reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->reflectedRadiance * color + 
                localContributionImportance * calculateLocalContribution(lightPos, shadowRayType);
        //std::cout << std::endl << "color: (" << color.x << ", " << color.y << ", " << color.z << ")" << std::endl;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay != NULL){
        color = (reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->reflectedRadiance + 
                (importance - reflectionRay->reflectedRadiance) * refractionRay->calculateColor(lightPos, shadowRayType)) * color + 
                localContributionImportance * calculateLocalContribution(lightPos, shadowRayType);
        //std::cout << std::endl << "color: (" << color.x << ", " << color.y << ", " << color.z << ")" << std::endl;
        //std::cout << "importance: " << (importance - reflectionRay->reflectedRadiance) << std::endl;
        //color2 * importance = refractionRay->calculateColor();
        //color = color1 + color2;
    //color *= calculateLocalContribution(lightPos);
    } else {
        color = glm::dvec3(0.0, 0.0, 0.0);
    }
    
    return color;
}

/**
 *
 * KANSKE MÅSTE MECKA, MEN NU FICK DET RECKA
 *
 */
glm::dvec3 Ray::calculateLocalContribution(glm::dvec3 lightPos, int shadowRayType){
    glm::dvec3 localLighting(0.0, 0.0, 0.0);
    double diffuseConstant = 0.5;
    double specularConstant = 0.5;
    double highlightConstant = 10.0;
    glm::dvec3 lightSourceColor(1.0, 1.0, 1.0);

    glm::dvec3 shadowRay = glm::normalize(lightPos - intersectionPoint);
    glm::dvec3 invShadowRay = glm::normalize(intersectionPoint - lightPos);
    glm::dvec3 shadowRayReflection = glm::normalize(invShadowRay - 2 * (glm::dot(invShadowRay, intersectionNormal)) * intersectionNormal);
    glm::dvec3 viewDirection = glm::normalize(startingPoint - intersectionPoint);

    if(shadowRayType != 3)
        return glm::dvec3(0.0, 0.0, 0.0);

    if(intersectionType == 2)
        localLighting = -(diffuseConstant * (glm::dot(shadowRay, intersectionNormal)) * lightSourceColor);
    else
        localLighting = diffuseConstant * (glm::dot(shadowRay, intersectionNormal)) * lightSourceColor;

    if(intersectionType == 0 || intersectionType == 1){
        //std::cout << std::endl << "color: (" << color.x << ", " << color.y << ", " << color.z << ")" << std::endl;
        //std::cout << std::endl << "diff: (" << localLighting.x << ", " << localLighting.y << ", " << localLighting.z << ")" << std::endl;
        localLighting += specularConstant * pow(glm::dot(shadowRayReflection, viewDirection), highlightConstant) * lightSourceColor;
        //std::cout << std::endl << "spec + diff: (" << localLighting.x << ", " << localLighting.y << ", " << localLighting.z << ")" << std::endl;
    }
    return localLighting;
}

void Ray::calculateImportance(double refractiveIndex, bool transparent){
    double n1 = 1.0;
    double n2 = 1.0;
    
    if(insideObject)
        n1 = refractiveIndex;
    else 
        n2 = refractiveIndex;
    if(refractionRay == NULL && reflectionRay != NULL){
        importance = 0.3;
        reflectionRay->reflectedRadiance = importance;
        //std::cout << std::endl << "fresnel: " << pow((n1 - n2) / (n1 + n2), 2) * importance << std::endl;
    }
    
    if(reflectionRay != NULL && refractionRay != NULL && !finalNode && transparent == true){
        importance = 0.3;
        reflectionRay->reflectedRadiance = pow((n1 - n2) / (n1 + n2), 2) * importance;
        //std::cout << std::endl << "fresnel: " << reflectionRay->reflectedRadiance << std::endl;
        //std::cout << "importance: " << importance << std::endl;
        refractionRay->transmittedRadiance = importance - reflectionRay->importance;
    }
    if(reflectionRay == NULL && refractionRay == NULL){
        importance = 0.3;
        reflectedRadiance = importance;
        transmittedRadiance = importance - reflectedRadiance;
        //std::cout << std::endl << ""
    }
    //importance = 0.3;
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

int Ray::getIntersectinType(){
    return intersectionType;
}

void Ray::setIntersectionNormal(glm::dvec3 n){
    intersectionNormal = n;
}

