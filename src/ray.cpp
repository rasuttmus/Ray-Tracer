#include "ray.h"

Ray::Ray(glm::dvec3 d, glm::dvec3 s):
		 direction(d), startingPoint(s){
}



glm::dvec3 Ray::calculateColor(glm::dvec3 lightPos, int shadowRayType) {
    
    double localContributionImportance = 1.0 - importance;

    //recursive function thats goes through all child rays. 
    if(finalNode == true){
        color = color * importance + localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay == NULL){
        color = reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->reflectedRadiance * color + 
                localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay != NULL){
        color = (reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->reflectedRadiance + 
                (importance - reflectionRay->reflectedRadiance) * refractionRay->calculateColor(lightPos, shadowRayType)) * color + 
                localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;

        /*if(intersectionType == 1){
            color = (reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->reflectedRadiance + 
                (importance - reflectionRay->reflectedRadiance) * refractionRay->calculateColor(lightPos, shadowRayType)) * color;
         } */
    
    
    }
    return color;
}

glm::dvec3 Ray::calculateLocalContribution(glm::dvec3 lightPos, int shadowRayType){
    glm::dvec3 localLighting(0.0, 0.0, 0.0);
    double diffuseConstant = 1.0;
    double specularConstant = 5.0;
    double highlightConstant = 10.0;
    glm::dvec3 lightSourceColor(1.0, 1.0, 1.0);

    glm::dvec3 shadowRay = glm::normalize(lightPos - intersectionPoint);
    glm::dvec3 invShadowRay = glm::normalize(intersectionPoint - lightPos);
    glm::dvec3 shadowRayReflection = glm::normalize(invShadowRay - 2 * (glm::dot(invShadowRay, intersectionNormal)) * intersectionNormal);
    glm::dvec3 viewDirection = glm::normalize(startingPoint - intersectionPoint);

    //if shadowray does not intersect with lightsource
    if(shadowRayType != 3){
        return glm::dvec3(0.0,0.0,0.0);
    }

    //calculate diffuse phong shading
    if(intersectionType == 2)
        localLighting = diffuseConstant * (glm::dot(shadowRay, -intersectionNormal)) * lightSourceColor;
    else
        localLighting = diffuseConstant * (glm::dot(shadowRay, intersectionNormal)) * lightSourceColor;

    //If object is specular, add specular phong shading
    if(intersectionType == 0 || intersectionType == 1){
        localLighting += specularConstant * pow(glm::dot(shadowRayReflection, viewDirection), highlightConstant) * lightSourceColor;
    }

    return localLighting;
}

void Ray::calculateImportance(double refractiveIndex, bool transparent){
    double n1 = 1.0;
    double n2 = 1.0;
   
    if(transparent)
    importance = 0.9;

    if(insideObject)
        n1 = refractiveIndex;
    else 
        n2 = refractiveIndex;
    
    if(refractionRay == NULL && reflectionRay != NULL){
        reflectionRay->reflectedRadiance = importance;
    }
    
    if(reflectionRay != NULL && refractionRay != NULL && !finalNode && transparent == true){
        reflectionRay->reflectedRadiance = pow((n1 - n2) / (n1 + n2), 2) * importance;
        refractionRay->transmittedRadiance =  100.0 * (importance - reflectionRay->importance);
    }
    if(reflectionRay == NULL && refractionRay == NULL){
        reflectedRadiance = importance;
        transmittedRadiance = importance - reflectedRadiance;
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

