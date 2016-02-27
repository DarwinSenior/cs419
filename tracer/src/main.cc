
#include <iostream>
#include <opencv2/opencv.hpp>
#include "scene.h"
#include "directional_light.h"
#include "sphere.h"
#include "triangle.h"
#include "material.h"
#include "sample.h"

using namespace std;
using namespace RT;
using namespace cv;

int main() {

    auto scene = Scene();
    auto sphere1 = Sphere(Vec3f(0.0, 0.0, 5.0), 2);
    auto triangle1 = Triangle(Vec3f(-1.0, -1.0, 4.0), Vec3f(0.0, 1.0, 3.0),
                              Vec3f(1.0, 0.0, 1.0));
    auto sphere2 = Sphere(Vec3f(1.0, 2.0, 2.0), 0.5);
    auto sphere3 = Sphere(Vec3f(-1.0, -2.0, 3.0), 1);
    auto material1 = Material();
    material1.colour = Vec3f(1.0, 1.0, 0.0);
    auto material2 = Material();
    material2.colour = Vec3f(0, 1, 1);
    auto material3 = Material();
    material3.colour = Vec3f(1, 0, 1);
    auto material4 = Material();
    material4.colour = Vec3f(0.5, 0.5, 0.5);
    scene.lights().push_back(
        light_ptr(new DirLight(Vec3f(0.0, -1.0, -1.0), 1)));
    scene.lights().push_back(
        light_ptr(new DirLight(Vec3f(-1.0, 0.0, -1.0), 1)));
    scene.objects().push_back(object_ptr(new Object(material1, triangle1)));
    scene.objects().push_back(object_ptr(new Object(material2, sphere1)));
    scene.objects().push_back(object_ptr(new Object(material3, sphere2)));
    scene.objects().push_back(object_ptr(new Object(material4, sphere3)));

    const int im_size = 500;
    Mat im1 = scene.render(im_size, uniform_sample);
    // namedWindow("render perspective", CV_WINDOW_AUTOSIZE);
    // imshow("render perspective", im1);
    scene.camera().move(1);
    scene.camera().yaw(0.2);
    scene.camera().roll(0.2);
    Mat im2 = scene.render(im_size, uniform_sample);
    // namedWindow("render different perspective", CV_WINDOW_AUTOSIZE);
    // imshow("render different perspective", im2);
    scene.screen().set_othorgraphic();
    Mat im3 = scene.render(im_size, uniform_sample);
    // namedWindow("render orthoganal", CV_WINDOW_AUTOSIZE);
    // imshow("render orthoganal", im3);

    scene.lights().push_back(light_ptr(new DirLight(Vec3f(0, 0, 1), 1)));
    Mat im4 = scene.render(im_size, uniform_sample);

    Mat im5 = scene.render(im_size, multi_jittered);
    im1.convertTo(im1, CV_8U, 255.0, 1 / 255.0);
    im2.convertTo(im2, CV_8U, 255.0, 1 / 255.0);
    im3.convertTo(im3, CV_8U, 255.0, 1 / 255.0);
    im4.convertTo(im4, CV_8U, 255.0, 1 / 255.0);
    im5.convertTo(im5, CV_8U, 255.0, 1 / 255.0);

    imwrite("image_perspective.png", im1);
    imwrite("image_another_perspective.png", im2);
    imwrite("image_orthoganal.png", im3);
    imwrite("image_uniform_sample.png", im4);
    imwrite("image_multi_jittered.png", im5);
    return 0;
}
