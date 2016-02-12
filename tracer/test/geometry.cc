#include "catch.hpp"
#include "../src/geometry.h"
#include "../src/triangle.h"
#include "../src/plane.h"
#include "../src/sphere.h"
#include "../src/ray.h"
#include "../src/intersect.h"
#include <opencv2/opencv.hpp>
#include <utility>

TEST_CASE("test virtual", "[geometry]"){
    using namespace std;
    using namespace cv;

    Geometry* triangle = new Triangle(Vec3f(1.0, 0.0, 6.0), Vec3f(0.0, 1.0, 6.0), Vec3f(1.0, 1.0, 6.0));
    auto inter = Intersect();

    auto ray = Ray();
    Vec3f ux = Vec3f(1.0, 0.0, 0.0);
    Vec3f uy = Vec3f(0.0, 1.0, 0.0);
    Vec3f uz = Vec3f(0.0, 0.0, 1.0);

    ray.d = uz;
    ray.o = 0.5*ux+0.5*uy;
    triangle->intersect(ray, inter);
    REQUIRE(inter.dist == Approx(6.0));
    REQUIRE(inter.norm == -uz);
    REQUIRE(inter.pos == 0.5*(ux+uy)+6*uz);
}

TEST_CASE("test triangle", "[geometry]"){
    using namespace std;
    using namespace cv;

    float inf = std::numeric_limits<float>::infinity();
    auto inter = Intersect();
    Vec3f ux = Vec3f(1.0, 0.0, 0.0);
    Vec3f uy = Vec3f(0.0, 1.0, 0.0);
    Vec3f uz = Vec3f(0.0, 0.0, 1.0);

    Triangle triangle(Vec3f(1.0, 0.0, 6.0), Vec3f(0.0, 1.0, 6.0), Vec3f(1.0, 1.0, 6.0));
    SECTION("hit triangle"){
        auto ray = Ray();
        ray.d = uz;
        ray.o = 0.5*ux+0.5*uy;
        triangle.intersect(ray, inter);
        REQUIRE(inter.dist == Approx(6.0));
        REQUIRE(inter.norm == -uz);
        REQUIRE(inter.pos == 0.5*(ux+uy)+6*uz);
    }

    SECTION("miss triange"){
        auto ray = Ray();
        ray.d = uz;
        ray.o = 2*ux+2*uy;
        triangle.intersect(ray, inter);
        REQUIRE(inter.dist == inf);
    }
}

TEST_CASE("test sphere", "[geometry]"){

    using namespace std;
    using namespace cv;

    float inf = std::numeric_limits<float>::infinity();
    auto inter = Intersect();
    Vec3f ux = Vec3f(1.0, 0.0, 0.0);
    Vec3f uy = Vec3f(0.0, 1.0, 0.0);
    Vec3f uz = Vec3f(0.0, 0.0, 1.0);

    Sphere sphere(6*uz, 2);
    SECTION("hit the sphere"){
        auto ray = Ray();
        ray.d = uz;
        ray.o = 0*uz;
        sphere.intersect(ray, inter);
        REQUIRE(inter.dist == Approx(6-2));
        REQUIRE(inter.norm == -uz);
        REQUIRE(inter.pos == 4*uz);
    }
    SECTION("miss the sphere"){
        auto ray = Ray();
        ray.d = uz;
        ray.o = 1.5*ux+1.5*uy;
        sphere.intersect(ray, inter);
        REQUIRE(inter.dist == inf);
    }

}

