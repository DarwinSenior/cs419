#include "PointLight.h"

using namespace std;

PointLight::PointLight() : PointLight(1.0, arr3(1.0, 1.0, 1.0), vec3()) {}

PointLight::PointLight(float intensity, arr3 color, vec3 pos)
    : Light(), m_pos(pos), m_intensity(intensity), m_color(color) {}

vec3 PointLight::direction(const Intersect& inter) const {
    return (inter.pos - m_pos).normalized();
}

arr3 PointLight::L(const Intersect&) const { return m_intensity * m_color; }

float PointLight::dist(const Intersect& inter) const {
    auto diff = inter.pos - m_pos;
    return sqrt(diff.dot(diff));
}
