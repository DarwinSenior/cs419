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
#include "img_util.h"
using namespace std;
using namespace cv;

int main() {
    Scene scene;
    auto& cam = scene.camera();
    auto& screen = scene.screen();
    auto& objects = scene.objects();
    auto& lights = scene.lights();
    cam.move(vec3(0, 0, -3));
    cam.pitch(-0.1);
    screen.focus(1.5);
    screen.size(arr2(1, 1));
    auto white = vec3(1.0, 1.0, 1.0);
    // auto light_pos = vec3(-1, 0, -1);
    auto red = vec3(0, 0, 1);
    auto blue = vec3(1, 0, 0);

    mat_ptr mat_p = make_shared<PhongMaterial>(0.25, 0.75, 5, red);
    mat_ptr mat_p2 = make_shared<PhongMaterial>(0.5, 0.5, 0, blue);
    vector<geo_ptr> geos;
    RT::read_meshes("cow.obj", geos);
    RT::read_meshes("box.obj", geos);
    vector<Sphere> spheres;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            for (size_t k = 0; k < 10; k++) {
                spheres.push_back(Sphere(
                    vec3((i - 5) * 0.2, (j - 5) * 0.2, (k - 5) * 0.2 + 1),
                    0.1));
            }
        }
    }
    geo_ptr plane_p = make_shared<Plane>((vec3(0, -1, -0.1)).normalized(), -3);
    objects.push_back(Object(make_shared<BHV<Sphere>>(spheres), mat_p));
    // objects.push_back(Object(geos[1], mat_p));
    objects.push_back(Object(plane_p, mat_p2));

    // lights.push_back(make_shared<PointLight>(0.5, white, -light_pos));
    lights.push_back(make_shared<AmbientLight>(0.1, white));
    lights.push_back(
        make_shared<PointLight>(1, white, cam.pos() - 0.5 * cam.front()));
    lights.push_back(make_shared<PointLight>(0.5, white, vec3(0, -5, 0)));
    // lights.push_back(
    //     make_shared<DirectionLight>(0.3, white, (vec3(0, -1, 1)).normalized()));
    scene.shadow(false);
    auto img = scene.render(500, RT::uniform_sample);
    RT::write_png("first.png", img);
    return 0;
}
