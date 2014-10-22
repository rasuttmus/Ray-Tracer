#include "camera.h"

Camera::Camera(float p, glm::vec2 xRes, glm::vec2 yRes, int imgResX, int imgResY, int r):
raysPerPixel(r)
{
    viewPlaneResolution.x = xRes.y - xRes.x;
    viewPlaneResolution.y = yRes.y - yRes.x;
    position.z = p;
    viewDirection = glm::vec3(viewPlaneResolution.x, viewPlaneResolution.y, 1);
    createPixels(imgResX, imgResY);
    //std::cout << "xres: " << viewPlaneResolution.x << "   yres: " << viewPlaneResolution.y << std::endl;

}

void Camera::renderImage() {
    std::cout << "raysPerPixel: " << raysPerPixel << std::endl;
    // Loop ove all pixels
}

void Camera::mappingFunction() {

}

void Camera::displayImage() {

}

void Camera::createPixels(int imgResX, int imgResY){
    for(int i = 0; i < imgResX; i++) {
        for (int j = 0; j < imgResY; j++) {
            pixels.push_back(new Pixel(raysPerPixel, viewPlaneResolution.x/imgResX, i/* - imgResX/2*/, j/* - imgResX/2*/, position));
            
        }
        std::cout << "i - imgResX / 2: " << i - imgResX/2 << std::endl;
    }
}

void Camera::addShape(Shape *s){
    for(std::vector<Pixel *>::iterator it = pixels.begin(); it != pixels.end(); ++it)
        (*it)->shapes.push_back(s);
}