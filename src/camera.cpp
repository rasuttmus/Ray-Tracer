#include "camera.h"

Camera::Camera(float p, glm::vec2 xRes, glm::vec2 yRes, int r):
raysPerPixel(r)
{
    viewPlaneResolution.x = xRes.y - xRes.x;
    viewPlaneResolution.y = yRes.y - yRes.x;
    position.z = p;
    //viewDirection.


}

void Camera::renderImage() {
    std::cout << "raysPerPixel: " << raysPerPixel << std::endl;
}

void Camera::mappingFunction() {

}

void Camera::displayImage() {

}