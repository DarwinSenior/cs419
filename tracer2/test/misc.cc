#include <iostream>
#include <limits>
#include <opencv2/opencv.hpp>
#include "catch.hpp"

#include "../src/typedef.h"

using namespace std;
using namespace Eigen;

namespace {
template <class T>
T log2i(T number) {
    int count = 0;
    while (number) {
        count++;
        number = number >> 1;
    }
    return count;
}
}

TEST_CASE("MISC", "[MISC]") { REQUIRE(INF == INF); }
TEST_CASE("VECTOR", "[MISC]") {
    for (int i = 0; i < 100; i++) {
        auto v1 = vec3(rand() % 10, rand() % 10, rand() % 10);
        auto v2 = vec3(rand() % 10, rand() % 10, rand() % 10);
        auto vec1 = v1.cwiseProduct(v2);
        auto vec2 = vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
        REQUIRE(vec1 == vec2);
    }
}
TEST_CASE("LOG", "[MISC]") {
    REQUIRE(log2i(1) == 1);
    REQUIRE(log2i(4) == 3);
    REQUIRE(log2i(60) == 6);
}

TEST_CASE("Eigen sanity check", "[MISC]"){
    Eigen::MatrixXd m(2,2);
    m(0, 0) = 3;
    auto m2 = m * 2;
    REQUIRE(m2(0,0) == 6);
}
