#include <iostream>
#include "scene.h"
#include "directional_light.h"
#include "sphere.h"
#include "triangle.h"
#include "material.h"
#include "sample.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <cppformat/format.h>
using namespace std;
using namespace cv;
using namespace RT;
using namespace fmt;


int main(){
    auto scene = Scene();
    auto sphere = Sphere(Vec3f(0.0, 0.0, 5.0), 2);
    auto material = Material();
    material.colour = Vec3f(1, 1, 0);
    scene.objects().push_back(object_ptr(new Object(material, sphere)));

    scene.lights().push_back(light_ptr(new DirLight(Vec3f(0.0, -1.0, -1.0), 1)));

    const int im_size = 200;
    for (size_t i=0; i<50; i++){
        float first = std::rand();
        float second = std::rand();
        scene.lights().pop();
        scene.lights().push_back(light_ptr(new DirLight(Vec3f(first, second, -1.0), 1)));

        Mat im = scene.render(im_size, uniform_sample);
        auto file_name = fmt::format("generate/image{}.png", i);
        imwrite(file_name, im);
    }
    return 0;
}
