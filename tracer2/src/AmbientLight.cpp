
#include "AmbientLight.h"

using namespace std;
using namespace cv;

AmbientLight::AmbientLight(float intensity, Vec3f color)
    : Light(), m_intensity(intensity), m_color(color) {}

AmbientLight::AmbientLight() : AmbientLight(1.0, Vec3f(1.0, 1.0, 1.0)) {}

Vec3f AmbientLight::direction(const Intersect& inter) const { return -inter.norm; }

Vec3f AmbientLight::L(const Intersect&) const { return m_intensity * m_color; }

float AmbientLight::dist(const Intersect&) const { return 0; }
