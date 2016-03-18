#include "../src/reader.h"
#include "../src/BHV.cpp"
#include "catch.hpp"
#include "../src/typedef.h"

using namespace std;
using namespace cv;
using namespace RT;

TEST_CASE("read examples", "[mesh]") {
    vector<geo_ptr> geometries;
    bool result = read_meshes("box.obj", geometries);
    REQUIRE(result);
    Ray ray;
    ray.o = vec3(-1, 0, 0);
    ray.d = vec3(1, 0, 0);
    Intersect inter(ray);
    BHV<Triangle>* bounder_p = (BHV<Triangle>*)geometries[0].get();
    // bounder_p->print();
    bool hit = geometries[0]->intersect(ray, inter);
    REQUIRE(hit);
    REQUIRE(inter.dist == 0.5);
    REQUIRE(inter.pos == vec3(-0.5, 0, 0));
    REQUIRE(inter.norm == -ray.d);
}

TEST_CASE("print mesh", "[mesh]"){
    vector<geo_ptr> geometries;
    bool result = read_meshes("cow.obj", geometries);
    REQUIRE(result);
    BHV<Triangle>* bounder_p = (BHV<Triangle>*)geometries[0].get();
    // bounder_p->print();
}
