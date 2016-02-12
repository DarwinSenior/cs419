#include "catch.hpp"
#include "../src/camera.h"
#include "../src/ray.h"
#include "../src/screen.h"
#include <opencv2/opencv.hpp>

TEST_CASE("Camera model", "[camera]"){
    using namespace std;
    using namespace cv;

    auto cam = Camera();
    Vec3f ux = Vec3f(1.0, 0.0, 0.0);
    Vec3f uy = Vec3f(0.0, 1.0, 0.0);
    Vec3f uz = Vec3f(0.0, 0.0, 1.0);
    REQUIRE(cam.front() == uz);
    REQUIRE(cam.up() == uy);
    REQUIRE(cam.pos() == Vec3f());

    SECTION("camera is moveable"){
        cam.move(3);
        cam.move(-3);

        REQUIRE(cam.front() == uz);
        REQUIRE(cam.up() == uy);
        REQUIRE(cam.pos() == Vec3f());

        cam.pitch(0.5);
        cam.pitch(-0.5);

        REQUIRE(cam.front() == uz);
        REQUIRE(cam.up() == uy);
        REQUIRE(cam.pos() == Vec3f());

        cam.roll(0.5);
        cam.roll(-0.5);

        REQUIRE(cam.front() == uz);
        REQUIRE(cam.up() == uy);
        REQUIRE(cam.pos() == Vec3f());

        cam.yaw(0.5);
        cam.yaw(-0.5);

        REQUIRE(cam.front() == uz);
        REQUIRE(cam.up() == uy);
        REQUIRE(cam.pos() == Vec3f());
    }
    SECTION("camera is rotatable"){
        const float pi = atan(1)*4;
        cam.yaw(pi/2);
    }

}

TEST_CASE("test screen", "[camera]"){
    using namespace std;
    using namespace cv;
    Screen screen(Size2f(4, 4), 3);
    Ray ray;
    auto cam = Camera();
    Vec3f ux = Vec3f(1.0, 0.0, 0.0);
    Vec3f uy = Vec3f(0.0, 1.0, 0.0);
    Vec3f uz = Vec3f(0.0, 0.0, 1.0);
    SECTION("shoot perspective"){

        screen.shoot_ray(cam, 0.5, 0.5, ray);
        REQUIRE(ray.o == Vec3f());
        REQUIRE(ray.d == uz);

        screen.shoot_ray(cam, 0, 0, ray);
        REQUIRE(ray.o == -2*ux-2*uy+0*uz);
        REQUIRE(ray.d == normalize(-2*ux-2*uy+3*uz));
    }

    SECTION("shoot orthorganal"){
        screen.set_othorgraphic();
        REQUIRE(screen.focus() == numeric_limits<float>::infinity());
        screen.shoot_ray(cam, 0.5, 0.5, ray);
        REQUIRE(ray.o == Vec3f());
        REQUIRE(ray.d == cam.front());
        screen.shoot_ray(cam, 0, 0, ray);
        REQUIRE(ray.o == -2*ux-2*uy);
        REQUIRE(ray.d == cam.front());
        screen.shoot_ray(cam, 0.3, 0.3, ray);
        REQUIRE(ray.d == cam.front());
        REQUIRE(cam.front() == uz);
    }
}
