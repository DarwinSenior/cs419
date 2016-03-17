#include "PointLight.h"

using namespace std;
using namespace cv;

PointLight::PointLight() : PointLight(1.0, Vec3f(1.0, 1.0, 1.0), Vec3f()) {}

PointLight::PointLight(float intensity, Vec3f color, Vec3f pos)
    : Light(), m_pos(pos), m_intensity(intensity), m_color(color) {}

Vec3f PointLight::direction(const Intersect& inter) const {
    return normalize(inter.pos - m_pos);
}

Vec3f PointLight::L(const Intersect&) const { return m_intensity * m_color; }

float PointLight::dist(const Intersect& inter) const {
    auto diff = inter.pos - m_pos;
    return sqrt(diff.dot(diff));
}
