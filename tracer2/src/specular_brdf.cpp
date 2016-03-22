#include "specular_brdf.h"
#include <cmath>

using namespace cv;
using namespace std;

SpecularBRDF::SpecularBRDF(float k, float alpha) : m_k(k), m_alpha(alpha) {}

Vec3f SpecularBRDF::f(const Vec3f& n, const Vec3f& w_i,
                      const Vec3f& w_o) const {
    float reflect = -(w_i - 2 * w_i.dot(n) * n).dot(w_o);
    return m_k * pow(max(reflect, 0.0f), m_alpha) * Vec3f(1, 1, 1);
}
