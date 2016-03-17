#include "diffuse_brdf.h"

using namespace std;
using namespace cv;

DiffuseBRDF::DiffuseBRDF(float k, Vec3f colour) : m_k(k), m_colour(colour) {}

Vec3f DiffuseBRDF::f(const Vec3f&, const Vec3f&, const Vec3f&) const {
    return m_k * m_colour;
}
