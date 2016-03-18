#include "transformer.h"

#include <cmath>

using namespace cv;
using namespace std;

namespace {
Matx44f I(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
// Matx44f rotation(int idx, float theta){
//     int i1 = (idx+1)%3;
//     int i2 = (idx+2)%3;
//     Matx44f rot(I);
//     sin_theta = sin(theta);
//     cos_theta = cos(theta);
//     rot[i1][i1] = cos_theta;
//     rot[i2][i1] = sin_theta;
//     rot[i1][i2] = -sin_theta;
//     rot[i2][i1] = cos_theta;
}
