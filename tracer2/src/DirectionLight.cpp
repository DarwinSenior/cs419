#include "DirectionLight.h"

using namespace std;
using namespace cv;

DirectionLight::DirectionLight(float intensity, Vec3f color, Vec3f dir)
    : Light(), m_color(color), m_dir(dir), m_intensity(intensity) {}

DirectionLight::DirectionLight()
    : DirectionLight(1.0, Vec3f(1.0, 1.0, 1.0), Vec3f(0.0, 0.0, 1.0)){};

Vec3f DirectionLight::direction(const Intersect&) const { return m_dir; }

Vec3f DirectionLight::L(const Intersect&) const { return m_intensity * m_color; }

float DirectionLight::dist(const Intersect&) const {
    // return std::numeric_limits<float>::infinity();
    return 100;
}
