#include "../src/light.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include "../src/AmbientLight.h"
#include "../src/DirectionLight.h"
#include "../src/PhongMaterial.h"
#include "../src/PointLight.h"
#include "../src/plane.h"
#include "../src/reader.h"
#include "../src/scene.cpp"
#include "catch.hpp"

using namespace std;
using namespace RT;
namespace {}

TEST_CASE("basic light testing", "[light]") {
    vector<geo_ptr> geometries;
    read_meshes("box.obj", geometries);
    Vec3f colour(1, 1, 1);
    Vec3f dir(1, 0, 0);
    Vec3f pos(-2, 0, 0);
    Ray ray;
    ray.o = Vec3f(-1, 0, 0);
    ray.d = dir;
    light_ptr light_p1 = make_shared<AmbientLight>(1, colour);
    light_ptr light_p2 = make_shared<PointLight>(1, colour, dir);
    light_ptr light_p3 = make_shared<DirectionLight>(1, colour, pos);

    Intersect inter(ray);
    geometries[0]->intersect(ray, inter);

    REQUIRE(light_p1->L(inter) == colour);
    REQUIRE(light_p2->L(inter) == colour);
    REQUIRE(light_p3->L(inter) == colour);
    REQUIRE(light_p1->dist(inter) == 0);
    REQUIRE(light_p2->dist(inter) == (1.5));
    REQUIRE(light_p3->dist(inter) > 10);
}

TEST_CASE("shadow", "[light]") {
    vector<geo_ptr> geos;
    read_meshes("box.obj", geos);
    vector<Object> objects;

    Vec3f colour(0, 0, 1);
    Vec3f dir(1, 0, 0);
    Vec3f pos(-2, 0, 0);

    mat_ptr mat_p = make_shared<PhongMaterial>(1, 1, 5, colour);
    light_ptr light_p1 = make_shared<AmbientLight>(1, colour);
    light_ptr light_p2 = make_shared<PointLight>(1, colour, pos);
    light_ptr light_p3 = make_shared<DirectionLight>(1, colour, dir);
    objects.push_back(Object(geos[0], mat_p));

    Ray ray;
    Intersect inter(ray);
    inter.pos = Vec3f(-0.5, 0, 0);

    REQUIRE(not_shadowed(*light_p1, inter, objects));
    REQUIRE(not_shadowed(*light_p2, inter, objects));
    REQUIRE(not_shadowed(*light_p3, inter, objects));
}

TEST_CASE("surface", "[light]") {
    geo_ptr plane_p = make_shared<Plane>(Vec3f(0, 1, 0), 3);
    Vec3f white(1, 1, 1);
    light_ptr light_p1 = make_shared<PointLight>(0.5, white, Vec3f(0, 2, 3));
    Ray ray;
    ray.o = Vec3f(0, 0, 0);
}
