#include "ray.h"

Ray::Ray(glm::dvec3 d, glm::dvec3 s):
		 direction(d), startingPoint(s){
}



glm::dvec3 Ray::calculateColor(glm::dvec3 lightPos, int shadowRayType) {
    

    /* HÄR MECKAR VI!! SAKER Är BORTMARKERADE FÖR ATT TESTA ATT LOCALCONTRIBUTION ÄR FEL SAMT FÖR HÖG OCH REFRACTED CONTRIBUTION ÄR FÖR LÅG! (DÄRAV MÄRKLIGA KONSTATNER SOM SENARE SKA TAS BORT)
    ** KAN OCCKSÅ KONSTATERA ATT REFRAKTIONEN INTE ÄR KORREKT! MÅSTE SES ÖVER
    ** REFLECTED RADIANCE ÄR TOKIG! BLIR PYTTELITEN!
    ** LOCALCONTRIBUTION BLI FEL NÄR DET RÖR SIG OM ETT TRANSPARENT OBJEKT. FELET KAN KANSKE DÄRFÖR LIGGA I ATT DEN SAKNAR SHADOWRAY?
    ** GRYNIGHETEN HOS OGENOMSKINLIGA OBJEKT ORSAKAS AV SHADOWRAYSEN
    ** IMPORTANSEN VID GENOMSKINLIGA OBJEKT GÖR ATT REFLEKTIONEN BLIT JÄTTELITEN!
    */    
    //importance = 0.9;

    double localContributionImportance = 1.0 - importance;

    //recursive function thats goes through all child rays. 
    if(finalNode == true){
        color = color * importance + localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay == NULL){
        color = reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->getImportance() * color * 10.0
                 +  localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color;
    }
    else if(finalNode == false && reflectionRay != NULL && refractionRay != NULL){
       // std::cout << std::endl << "Reflected RADIANCE: " << reflectionRay->reflectedRadiance << std::endl;
        color = reflectionRay->calculateColor(lightPos, shadowRayType) * reflectionRay->getImportance() * color * 10.0
                + refractionRay->calculateColor(lightPos, shadowRayType) * refractionRay->getImportance() * color * 20.0
                /*+ localContributionImportance * calculateLocalContribution(lightPos, shadowRayType) * color*/;    
    }
    return color;
}

glm::dvec3 Ray::calculateLocalContribution(glm::dvec3 lightPos, int shadowRayType){
    glm::dvec3 localLighting(0.0, 0.0, 0.0);
    double diffuseConstant = 1.0;
    double specularConstant = 1.8;
    double highlightConstant = 2.0; // <-- VERKAR SOM DENNA MÅSTE VARA HELTAL FÖR ATT FUNKA?
    glm::dvec3 lightSourceColor(1.0, 1.0, 1.0);

    glm::dvec3 shadowRay = glm::normalize(lightPos - intersectionPoint);
    glm::dvec3 invShadowRay = glm::normalize(intersectionPoint - lightPos);
    glm::dvec3 shadowRayReflection = glm::normalize(invShadowRay - 2 * (glm::dot(invShadowRay, intersectionNormal)) * intersectionNormal);
    glm::dvec3 viewDirection = glm::normalize(startingPoint - intersectionPoint);

    //if shadowray does not intersect with lightsource
    if(shadowRayType != 3){
        //return glm::dvec3(0.0,0.0,0.0);
    }

    //calculate diffuse phong shading
    if(intersectionType == 2)
        localLighting = diffuseConstant * (glm::dot(shadowRay, -intersectionNormal)) * lightSourceColor;
    else
        localLighting = diffuseConstant * (glm::dot(shadowRay, intersectionNormal)) * lightSourceColor;

    //If object is specular, add specular phong shading
    if(intersectionType == 0 || intersectionType == 1){
        //std::cout << std::endl << "intersectionType =" << intersectionType << std::endl;
        localLighting += specularConstant * pow(glm::dot(shadowRayReflection, viewDirection), highlightConstant) * lightSourceColor;
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
        reflectionRay->setImportance(importance);
        //reflectedRadiance = importance;
    }
    
    if(reflectionRay != NULL && refractionRay != NULL && !finalNode && transparent == true){

        reflectionRay->setImportance(pow((n1 - n2) / (n1 + n2), 2) * importance);

        refractionRay->setImportance(importance - reflectionRay->getImportance());

    }
    if(reflectionRay == NULL && refractionRay == NULL){
        //reflectedRadiance = importance;
        //transmittedRadiance = importance - reflectedRadiance;
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

