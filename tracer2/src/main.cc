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
    cam.move(Vec3f(0, 0, -3));
    cam.pitch(-0.1);
    screen.focus(1.5);
    screen.size(Size2f(1, 1));
    auto white = Vec3f(1.0, 1.0, 1.0);
    // auto light_pos = Vec3f(-1, 0, -1);
    auto red = Vec3f(0, 0, 1);
    auto blue = Vec3f(1, 0, 0);

    mat_ptr mat_p = make_shared<PhongMaterial>(0.5, 1.5, 5, red);
    mat_ptr mat_p2 = make_shared<PhongMaterial>(1, 1, 0, blue);
    vector<geo_ptr> geos;
    RT::read_meshes("cow.obj", geos);
    RT::read_meshes("box.obj", geos);
    vector<Sphere> spheres;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            for (size_t k = 0; k < 10; k++) {
                spheres.push_back(Sphere(
                    Vec3f((i - 5) * 0.2, (j - 5) * 0.2, (k - 5) * 0.2 + 1),
                    0.1));
            }
        }
    }
    geo_ptr plane_p = make_shared<Plane>(normalize(Vec3f(0, -1, -0.3)), -3);
    objects.push_back(Object(make_shared<BHV<Sphere>>(spheres), mat_p));
    // objects.push_back(Object(geos[1], mat_p));
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
    namedWindow("show1");
    imshow("show1", img);
    scene.shadow(true);
    img = scene.render(500, RT::uniform_sample);
    namedWindow("show2");
    imshow("show2", img);
    waitKey(0);
    return 0;
}
