#include "camera.h"

Camera::Camera(float p, glm::vec2 xRes, glm::vec2 yRes, int imgResX, int imgResY, int r):
raysPerPixel(r)
{
    viewPlaneResolution.x = xRes.y - xRes.x;
    viewPlaneResolution.y = yRes.y - yRes.x;
    position.z = p;
    viewDirection = glm::vec3(viewPlaneResolution.x, viewPlaneResolution.y, 1);
    createPixels(imgResX, imgResY);

}

void Camera::renderImage() {
    std::cout << "raysPerPixel: " << raysPerPixel << std::endl;
}

void Camera::mappingFunction() {

}

void Camera::displayImage() {

}

void Camera::createPixels(int imgResX, int imgResY) {
    for(int i = 0; i < imgResX; i++) {
        for (int j = 0; j < imgResY; j++) {
            pixels.push_back(new Pixel(raysPerPixel, viewPlaneResolution.x/imgResX, i, j, position));
            std::cout << std::endl;
        }
    }
}