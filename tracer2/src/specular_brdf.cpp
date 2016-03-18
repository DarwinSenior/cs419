#include "specular_brdf.h"
#include <cmath>

using namespace std;

SpecularBRDF::SpecularBRDF(float k, float alpha) : m_k(k), m_alpha(alpha) {}

arr3 SpecularBRDF::f(const vec3& n, const vec3& w_i,
                      const vec3& w_o) const {
    float reflect = (w_i - 2 * w_i.dot(n) * n).dot(w_o);
    return m_k * pow(max(reflect, 0.0f), m_alpha) * arr3(1, 1, 1);
}
