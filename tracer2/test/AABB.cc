#include "../src/AABB.cpp"
#include "../src/BHV.h"
#include "../src/intersect.h"
#include "../src/intersect.h"
#include "../src/ray.h"
#include "../src/sphere.h"
#include "../src/triangle.h"
#include "catch.hpp"

namespace {
auto x = Vec3f(1, 0, 0);
auto y = Vec3f(0, 1, 0);
auto z = Vec3f(0, 0, 1);
auto zero = Vec3f(0, 0, 0);
auto t1 = Triangle(zero, x, y);
auto t2 = Triangle(zero, x, z);
auto t3 = Triangle(zero, y, z);
auto t4 = Triangle(x, x + y, x + z);
auto t5 = Triangle(y, y + x, y + z);
auto t6 = Triangle(z, x + z, y + z);
auto t7 = Triangle(x, y, x + y);
auto t8 = Triangle(y, z, y + z);
auto t9 = Triangle(x, z, x + z);
auto t10 = Triangle(x + y + z, x + y, x + z);
auto t11 = Triangle(x + y + z, y + x, y + z);
auto t12 = Triangle(x + y + z, x + z, y + z);
auto ts = vector<Triangle>({t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12});
auto s1 = Sphere(x, 3);
auto s2 = Sphere(y, 3);
auto s3 = Sphere(z, 3);
auto ss = vector<Sphere>({s1, s2, s3});
}

TEST_CASE("MAX and MIN", "[AABB]") {
    vector<Vec3f> vecs;
    vecs.push_back(Vec3f(1, 0, 0));
    vecs.push_back(Vec3f(0, 1, 0));
    vecs.push_back(Vec3f(0, 0, 1));
    REQUIRE(maximum(vecs) == Vec3f(1, 1, 1));
    REQUIRE(minimum(vecs) == Vec3f(0, 0, 0));
}

TEST_CASE("Spheres", "[AABB]") {
    AABB boxd(ss);
    AABB box;
    box = boxd;
    REQUIRE(box.min_p() == Vec3f(-3, -3, -3));
    REQUIRE(box.max_p() == Vec3f(4, 4, 4));
    REQUIRE(box.volume() == 7 * 7 * 7);
    REQUIRE(box.center() == Vec3f(0.5, 0.5, 0.5));
}

TEST_CASE("Bounding Box", "[AABB]") {
    AABB box(ts);
    REQUIRE(box.volume() == 1);
    REQUIRE(box.surface_area() == 6);
    REQUIRE(box.center() == Vec3f(0.5, 0.5, 0.5));
    REQUIRE(box.inside(Vec3f(0.3, 0.6, 0.7)));
}

TEST_CASE("AABB distance", "[AABB]") {
    AABB box(ts);
    Ray ray;
    ray.o = -x + 0.5 * y + 0.5 * z;
    ray.d = x;
    float dist = box.intersect(ray);
    REQUIRE(dist == 1);
    ray.o = 2 * y + 0.5 * x + 0.5 * z;
    ray.d = -y;
    dist = box.intersect(ray);
    REQUIRE(dist == 1);
    ray.o = -x - z + 0.5 * y;
    ray.d = normalize(x + z);
    cout << "ray.d " << ray.d << endl;
    dist = box.intersect(ray);
    REQUIRE(dist == Approx(sqrt(2)));
}

TEST_CASE("Triangle Split", "[BHV]") {
    vector<int> indices;
    for (size_t i = 0; i < ts.size(); i++) {
        indices.push_back(i);
    }
    auto bounder = BHV<Triangle>(ts, indices);
    Ray ray;
    ray.o = -y + 0.2 * x + 0.2 * z;
    ray.d = y;
    Intersect inter(ray);
    bounder.intersect(ray, inter);
    Intersect inter2(ray);
    for (auto& t : ts) {
        t.intersect(ray, inter2);
    }
    cout << inter.dist << endl;
    cout << inter2.dist << endl;
}
