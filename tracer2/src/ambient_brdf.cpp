#include "ambient_brdf.h"

using namespace std;
using namespace cv;

AmbientBRDF::AmbientBRDF(float k, Vec3f colour) : m_k(k), m_colour(colour) {}

Vec3f AmbientBRDF::f(const Vec3f&, const Vec3f&, const Vec3f&) const {
    return m_colour * m_k;
}
