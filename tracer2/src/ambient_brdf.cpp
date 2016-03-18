#include "ambient_brdf.h"

using namespace std;

AmbientBRDF::AmbientBRDF(float k, arr3 colour) : m_k(k), m_colour(colour) {}

arr3 AmbientBRDF::f(const vec3&, const vec3&, const vec3&) const {
    return m_k * m_colour;
}
