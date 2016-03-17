#include "../src/reader.h"
#include "catch.hpp"

using namespace std;
using namespace cv;
using namespace RT;

TEST_CASE("read examples", "[mesh]") {
    vector<geo_ptr> geometries;
    bool result = read_meshes("box.obj", geometries);
    REQUIRE(result);
    Ray ray;
    ray.o = Vec3f(-1, 0, 0);
    ray.d = Vec3f(1, 0, 0);
    Intersect inter(ray);
    bool hit = geometries[0]->intersect(ray, inter);
    REQUIRE(hit);
    REQUIRE(inter.dist == 0.5);
    REQUIRE(inter.pos == Vec3f(-0.5, 0, 0));
    REQUIRE(inter.norm == -ray.d);
}
