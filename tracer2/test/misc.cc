#include <iostream>
#include <limits>
#include <opencv2/opencv.hpp>
#include "catch.hpp"

using namespace std;
using namespace cv;

namespace {
float INF = std::numeric_limits<float>::infinity();
}

TEST_CASE("MISC", "[MISC]") { REQUIRE(INF == INF); }
TEST_CASE("VECTOR", "[MISC]") {
    for (int i = 0; i < 100; i++) {
        auto v1 = Vec3f(rand() % 10, rand() % 10, rand() % 10);
        auto v2 = Vec3f(rand() % 10, rand() % 10, rand() % 10);
        auto vec1 = v1.mul(v2);
        auto vec2 = Vec3f(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
        REQUIRE(vec1 == vec2);
    }
}
