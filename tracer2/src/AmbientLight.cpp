
#include "AmbientLight.h"

using namespace std;

AmbientLight::AmbientLight(float intensity, arr3 color)
    : Light(), m_intensity(intensity), m_color(color) {}

AmbientLight::AmbientLight() : AmbientLight(1.0, arr3(1.0, 1.0, 1.0)) {}

vec3 AmbientLight::direction(const Intersect& inter) const {
    return -inter.norm;
}

arr3 AmbientLight::L(const Intersect&) const { return m_intensity * m_color; }

float AmbientLight::dist(const Intersect&) const { return 0; }
