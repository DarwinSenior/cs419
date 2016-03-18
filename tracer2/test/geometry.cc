#include "../src/geometry.h"
#include <opencv2/opencv.hpp>
#include <random>
#include <utility>
#include "../src/intersect.h"
#include "../src/plane.h"
#include "../src/ray.h"
#include "../src/sphere.h"
#include "../src/triangle.h"
#include "../src/typedef.h"
#include "catch.hpp"

namespace {
float random() { return (float)rand() / ((float)RAND_MAX); }

vec3 rand_point() { return vec3(random(), random(), random()); }

Triangle rand_triangle() {
    return Triangle(rand_point(), rand_point(), rand_point());
}
}

TEST_CASE("test virtual", "[geometry]") {
    using namespace std;
    using namespace cv;

    Geometry* triangle = new Triangle(vec3(1.0, 0.0, 6.0), vec3(0.0, 1.0, 6.0),
                                      vec3(1.0, 1.0, 6.0));

    auto ray = Ray();
    vec3 ux = vec3(1.0, 0.0, 0.0);
    vec3 uy = vec3(0.0, 1.0, 0.0);
    vec3 uz = vec3(0.0, 0.0, 1.0);
    auto inter = Intersect(ray);

    ray.d = uz;
    ray.o = 0.5 * ux + 0.5 * uy;
    triangle->intersect(ray, inter);
    REQUIRE(inter.dist == Approx(6.0));
    REQUIRE(inter.norm == -uz);
    REQUIRE(inter.pos == 0.5 * (ux + uy) + 6 * uz);
}

TEST_CASE("test triangle", "[geometry]") {
    using namespace std;
    using namespace cv;

    float inf = std::numeric_limits<float>::infinity();
    vec3 ux = vec3(1.0, 0.0, 0.0);
    vec3 uy = vec3(0.0, 1.0, 0.0);
    vec3 uz = vec3(0.0, 0.0, 1.0);

    Triangle triangle(vec3(1.0, 0.0, 6.0), vec3(0.0, 1.0, 6.0),
                      vec3(1.0, 1.0, 6.0));
    SECTION("hit triangle") {
        auto ray = Ray();
        ray.d = uz;
        ray.o = 0.5 * ux + 0.5 * uy;
        auto inter = Intersect(ray);

        triangle.intersect(ray, inter);
        REQUIRE(inter.dist == Approx(6.0));
        REQUIRE(inter.norm == -uz);
        REQUIRE(inter.pos == 0.5 * (ux + uy) + 6 * uz);
    }

    SECTION("miss triange") {
        auto ray = Ray();
        ray.d = uz;
        ray.o = 2 * ux + 2 * uy;
        auto inter = Intersect(ray);
        triangle.intersect(ray, inter);
        REQUIRE(inter.dist == inf);
    }
}

TEST_CASE("random triangle test", "[geometry]") {
    using namespace std;
    using namespace cv;
    for (size_t i = 0; i < 20; i++) {
        auto triangle = rand_triangle();
        Ray ray;
        ray.o = rand_point() + vec3(1, 1, 1);
        ray.d = (triangle.center() - ray.o).normalized();
        Intersect inter(ray);
        triangle.intersect(ray, inter);
        REQUIRE(inter.dist < INF);
    }
}

TEST_CASE("random triangle inverse test", "[geometry]") {
    using namespace std;
    using namespace cv;
    for (size_t i = 0; i < 20; i++) {
        auto triangle = rand_triangle();
        Ray ray;
        ray.o = rand_point() + vec3(1, 1, 1);
        ray.d = -(triangle.center() - ray.o).normalized();
        Intersect inter(ray);
        triangle.intersect(ray, inter);
        REQUIRE(inter.dist == INF);
    }
}

TEST_CASE("test sphere", "[geometry]") {
    using namespace std;
    using namespace cv;

    float inf = std::numeric_limits<float>::infinity();
    vec3 ux = vec3(1.0, 0.0, 0.0);
    vec3 uy = vec3(0.0, 1.0, 0.0);
    vec3 uz = vec3(0.0, 0.0, 1.0);

    Sphere sphere(6 * uz, 2);
    SECTION("hit the sphere") {
        auto ray = Ray();
        auto inter = Intersect(ray);
        ray.d = uz;
        ray.o = 0 * uz;
        inter.noIntersection();
        sphere.intersect(ray, inter);
        REQUIRE(inter.dist == Approx(6 - 2));
        REQUIRE(inter.norm == -uz);
        REQUIRE(inter.pos == 4 * uz);
    }
    SECTION("miss the sphere") {
        auto ray = Ray();
        auto inter = Intersect(ray);
        ray.d = uz;
        ray.o = 1.5 * ux + 1.5 * uy;
        inter.noIntersection();
        sphere.intersect(ray, inter);
        REQUIRE(inter.dist == inf);
    }
}
