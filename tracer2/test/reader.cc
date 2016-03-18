#include "catch.hpp"
#include "../src/typedef.h"
#include "../src/img_util.h"

using namespace std;
using namespace cv;
using namespace RT;

TEST_CASE("write png", "[png]"){
    img_t image(200, 200);
    image = image + arr3(1,1,1);
    RT::write_png("example.png", image);
}

