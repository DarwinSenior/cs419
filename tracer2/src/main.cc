#include <iostream>

#include "AmbientLight.h"
#include "DirectionLight.h"
#include "PhongMaterial.h"
#include "PointLight.h"
#include "plane.h"
#include "reader.h"
#include "sample.h"
#include "scene.h"
#include "sphere.h"
using namespace std;
using namespace cv;

int main() {
    Scene scene;
    auto& cam = scene.camera();
    auto& screen = scene.screen();
    auto& objects = scene.objects();
    auto& lights = scene.lights();
    cam.move(Vec3f(0, 0, -1));
    cam.pitch(-0.1);
    screen.focus(1.5);
    screen.size(Size2f(0.5, 0.5));
    auto white = Vec3f(1.0, 1.0, 1.0);
    auto red = Vec3f(0, 0, 1);
    auto blue = Vec3f(1, 0, 0);
    auto green = Vec3f(0, 1, 0);

    mat_ptr mat_p = make_shared<PhongMaterial>(0.5, 1, 5, white);
    mat_ptr mat_p2 = make_shared<PhongMaterial>(1, 1, 0, green);
    vector<geo_ptr> geos;
    RT::read_meshes("bunny.obj", geos, 1);
    RT::read_meshes("box.obj", geos);
    vector<Sphere> spheres;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            for (size_t k = 0; k < 100; k++) {
                // spheres.push_back(Sphere(
                //     Vec3f((i - 5) * 0.2, (j - 5) * 0.2, (k - 5) * 0.2 + 1),
                //     0.1));
                objects.push_back(Object(
                    make_shared<Sphere>(
                        Vec3f((i - 5) * 0.2, (j - 5) * 0.2, (k - 5) * 0.2 + 1),
                        0.1),
                    mat_p));
            }
        }
    }
    geo_ptr plane_p = make_shared<Plane>(normalize(Vec3f(0, -1, -0.3)), -1);
    objects.push_back(Object(make_shared<BHV<Sphere>>(spheres), mat_p));
    objects.push_back(Object(plane_p, mat_p2));

    // lights.push_back(make_shared<PointLight>(0.5, white, -light_pos));
    lights.push_back(make_shared<AmbientLight>(0.1, white));
    lights.push_back(
        make_shared<PointLight>(0.5, white, cam.pos() + 0.5 * cam.front()));
    lights.push_back(make_shared<PointLight>(0.5, white, Vec3f(0, -5, 0)));
    // lights.push_back(
    //     make_shared<DirectionLight>(0.3, white, normalize(Vec3f(0, -1, 1))));
    scene.shadow(false);
    auto img = scene.render(500, RT::uniform_sample);
    Mat im2;
    img.convertTo(im2, CV_8U, 255.0, 1 / 255.0);
    return 0;
}
