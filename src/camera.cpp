#include "camera.h"

Camera::Camera(glm::dvec3 p, glm::dvec2 xRes, glm::dvec2 yRes, int imgResX, int imgResY, int r):
raysPerPixel(r)
{
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
    // Loop ove all pixels
    //Liten godbit från SimpleExample.cpp (måste fixas och donas men ska fungera enligt Emma)
    /*  
    
    Vec3<T> *image = new Vec3<T>[width * height], *pixel = image;
    T invWidth = 1 / T(viewPlaneResolution.x), invHeight = 1 / T(viewPlaneResolution.y);
    T fov = 30, aspectratio = viewPlaneResolution.x / T(viewPlaneResolution.y);
    T angle = tan(M_PI * 0.5 * fov / T(180));
    // Trace rays
    for (unsigned y = 0; y < viewPlaneResolution.y; ++y) {
        for (unsigned x = 0; x < viewPlaneResolution.x; ++x, ++pixel) {
            T xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            T yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vec3<T> raydir(xx, yy, -1);
            raydir.normalize();
            *pixel = trace(Vec3<T>(0), raydir, spheres, 0);
        }
    }
    


    // Save result to a PPM image (keep these flags if you compile under Windows)
    std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (unsigned i = 0; i < width * height; ++i) {
        ofs << (unsigned char)(std::min(T(1), image[i].x) * 255) << 
        (unsigned char)(std::min(T(1), image[i].y) * 255) <<
        (unsigned char)(std::min(T(1), image[i].z) * 255); 
    }
    ofs.close();
    delete [] image;

    */
}

void Camera::mappingFunction() {

}

void Camera::displayImage() {

}

void Camera::createPixels(int imgResX, int imgResY){
    for(int i = 0; i < imgResX; i++) {
        for (int j = 0; j < imgResY; j++) {
            pixels.push_back(new Pixel(raysPerPixel, viewPlaneResolution.x/imgResX, i - imgResX/2, j - imgResX/2, position));
            
        }
        std::cout << "i - imgResX / 2: " << i - imgResX/2 << std::endl;
    }
}

void Camera::addShape(Shape *s){
    for(std::vector<Pixel *>::iterator it = pixels.begin(); it != pixels.end(); ++it)
        (*it)->shapes.push_back(s);
}