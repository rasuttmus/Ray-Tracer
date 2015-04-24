#include "camera.h"

Camera::Camera(glm::dvec3 p, glm::dvec2 xRes, glm::dvec2 yRes, int imgResX, int imgResY, int r):
raysPerPixel(r), imageResolutionX(imgResX), imageResolutionY(imgResY){

    viewPlaneResolution.x = xRes.y - xRes.x;
    viewPlaneResolution.y = yRes.y - yRes.x;
    position = p;
    viewDirection = glm::dvec3(viewPlaneResolution.x, viewPlaneResolution.y, 1);
    createPixels(imgResX, imgResY);
}


double Camera::getRaysPerPixel(){
    return raysPerPixel;
}


void Camera::renderImage() {
    // Loop over all pixels    
    // Save result to a PPM image (keep these flags if you compile under Windows)
    std::ofstream ofs("./renderings/640x360_20rpp.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << imageResolutionY << " " << imageResolutionX << "\n255\n";
    /*for (std::vector<Pixel *>::iterator it = pixels.begin(); it != pixels.end(); ++it) {
        ofs << (unsigned char)(std::min(1.0, (*it)->getColorOfPixel().x) * 255) << 
        (unsigned char)(std::min(1.0, (*it)->getColorOfPixel().y) * 255) <<
        (unsigned char)(std::min(1.0, (*it)->getColorOfPixel().z) * 255); 

    }*/
    for(std::vector<glm::dvec3>::iterator it = pixelColors.begin(); it != pixelColors.end(); ++it) {
        ofs << (unsigned char)(std::min(1.0, (*it).x) * 255) << 
        (unsigned char)(std::min(1.0, (*it).y) * 255) <<
        (unsigned char)(std::min(1.0, (*it).z) * 255);
    }
    ofs.close();
}

void Camera::mappingFunction() {

}

void Camera::displayImage() {

}

void Camera::createPixels(int imgResX, int imgResY){
    for(int i = 0; i < imgResX; i++) {
        for (int j = 0; j < imgResY; j++) {
            pixels.push_back(new Pixel(raysPerPixel, viewPlaneResolution.y/imgResY, j - imgResY/2, i - imgResX/2, position));   
        }
    }
}

void Camera::addShape(Shape *s){
    for(std::vector<Pixel *>::iterator it = pixels.begin(); it != pixels.end(); ++it)
        (*it)->shapes.push_back(s);
}