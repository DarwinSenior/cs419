#include "DirectionLight.h"

using namespace std;

DirectionLight::DirectionLight(float intensity, arr3 color, vec3 dir)
    : Light(), m_color(color), m_dir(dir), m_intensity(intensity) {}

DirectionLight::DirectionLight()
    : DirectionLight(1.0, arr3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 1.0)){};

vec3 DirectionLight::direction(const Intersect&) const { return m_dir; }

arr3 DirectionLight::L(const Intersect&) const { return m_intensity * m_color; }

float DirectionLight::dist(const Intersect&) const {
    return std::numeric_limits<float>::infinity();
}
