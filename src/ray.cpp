#include "ray.h"

Ray::Ray(glm::dvec3 d, glm::dvec3 s):
		 direction(d), startingPoint(s){
}

/*Ray::~Ray() {
    //Ray *temp;
    std::cout << "börja delete rays" << std::endl;
    if(reflectionRay != NULL) {
        //temp = reflectionRay;
        std::cout << "börja delete reflectionRay" << std::endl;
        delete reflectionRay;
        std::cout << "klar delete reflectionRay" << std::endl;
    }

    if(refractionRay != NULL) {
        std::cout << "börja delete refractionRay" << std::endl;
        delete refractionRay;
        std::cout << "klar delete refractionRay" << std::endl;
    }
    std::cout << "börja delete rays" << std::endl;
}*/

glm::dvec3 Ray::calculateColor(glm::dvec3 lightPos, int shadowRayType) {  

    double localContributionImportance = 1.0 - importance;

    if(finalNode == true){
        color = importance * color + localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay == NULL){
        color = reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->importance * color * 40.0
                 + localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay != NULL && !finalNode){
        color = (reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->getImportance() * 40.0 + 
                (refractionRay->getImportance()) * refractionRay->calculateColor(lightPos, shadowRayType) * 40.0) * color
                + localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;
    }

    return color;
}

glm::dvec3 Ray::calculateLocalContribution(glm::dvec3 lightPos, int shadowRayType){
    glm::dvec3 localLighting(0.0, 0.0, 0.0);
    double diffuseConstant = 1.0;
    double specularConstant = 1.3;
    double highlightConstant = 20.0;
    glm::dvec3 lightSourceColor(1.0, 1.0, 1.0);

    glm::dvec3 shadowRay = glm::normalize(lightPos - intersectionPoint);
    glm::dvec3 invShadowRay = glm::normalize(intersectionPoint - lightPos);
    glm::dvec3 shadowRayReflection = glm::normalize(invShadowRay - 2 * (glm::dot(invShadowRay, intersectionNormal)) * intersectionNormal);
    glm::dvec3 viewDirection = glm::normalize(startingPoint - intersectionPoint);

    //calculate diffuse phong shading
    if(intersectionType == 2)
        localLighting = diffuseConstant * (glm::dot(shadowRay, -intersectionNormal)) * lightSourceColor;
    else
        localLighting = diffuseConstant * (glm::dot(shadowRay, intersectionNormal)) * lightSourceColor;

    //If object is specular, add specular phong shading
    if(intersectionType == 0 || intersectionType == 1){
        localLighting += specularConstant * pow(glm::dot(shadowRayReflection, viewDirection), highlightConstant) * lightSourceColor;
    }

    if(intersectionType == 3)
        return glm::dvec3(1.0, 1.0, 1.0);

    if(localLighting.x < 0.0)
        return glm::dvec3(0.1, 0.1, 0.1);

    if(localLighting.x > 1.0)
        return glm::dvec3(1.0, 1.0, 1.0);

    return localLighting;
}

void Ray::calculateImportance(double refractiveIndex, bool transparent){
    double n1 = 1.0;
    double n2 = 1.0;
    double critAngle = 0;
    double theta1 = 0;

    if(insideObject){
        n1 = refractiveIndex;
        critAngle = asin(n2/n1);
    }
    else 
        n2 = refractiveIndex;

    if(refractionRay == NULL && reflectionRay != NULL){
        reflectionRay->setImportance(importance);
    }
    
    if(reflectionRay != NULL && refractionRay != NULL && !finalNode && transparent == true){
        theta1 = acos(glm::dot(-intersectionNormal, direction));
        if(theta1 > 3.14159265358979323846 / 2)
            theta1 = theta1 - 3.14159265358979323846;

        reflectionRay->setImportance(pow((n1 - n2) / (n1 + n2), 2) * importance);

        refractionRay->setImportance(importance - reflectionRay->getImportance());
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

