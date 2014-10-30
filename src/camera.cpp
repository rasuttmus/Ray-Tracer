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
    std::cout << "raysPerPixel: " << raysPerPixel << std::endl;
    // Loop over all pixels
    //Liten godbit från SimpleExample.cpp (måste fixas och donas men ska fungera enligt Emma)
    
    // Save result to a PPM image (keep these flags if you compile under Windows)
    debug
    std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
    debug
    ofs << "P6\n" << imageResolutionY << " " << imageResolutionX << "\n255\n";
    debug
    for (std::vector<Pixel *>::iterator it = pixels.begin(); it != pixels.end(); ++it) {
        ofs << (unsigned char)(std::min(1.0, (*it)->getColorOfPixel().x) * 255) << 
        (unsigned char)(std::min(1.0, (*it)->getColorOfPixel().y) * 255) <<
        (unsigned char)(std::min(1.0, (*it)->getColorOfPixel().z) * 255); 
    }
    debug
    ofs.close();
}

void Camera::mappingFunction() {

}

void Camera::displayImage() {

}

void Camera::createPixels(int imgResX, int imgResY){
    for(int i = 0; i < imgResX; i++) {
        for (int j = 0; j < imgResY; j++) {
            pixels.push_back(new Pixel(raysPerPixel, viewPlaneResolution.y/imgResY, j - imgResY/2, i - imgResY/2, position));
            
        }
        //std::cout << "i - imgResX / 2: " << i - imgResX/2 << std::endl;
    }
}

void Camera::addShape(Shape *s){
    for(std::vector<Pixel *>::iterator it = pixels.begin(); it != pixels.end(); ++it)
        (*it)->shapes.push_back(s);
}