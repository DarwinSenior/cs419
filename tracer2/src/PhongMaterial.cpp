#include "PhongMaterial.h"

using namespace std;
using namespace cv;

namespace {}

PhongMaterial::PhongMaterial(float ks, float kd, float alpha, Vec3f colour)
    : m_diffuse(DiffuseBRDF(kd, colour)), m_specular(SpecularBRDF(ks, alpha)){};

Vec3f PhongMaterial::shade(const Intersect& inter, const Light& light) {
    Vec3f final_color;
    auto light_dir = light.direction(inter);
    auto L = light.L(inter);
    auto theta = max(-light_dir.dot(inter.norm), 0.0f);
    final_color +=
        m_diffuse.f(inter.norm, inter.raydir, light_dir).mul(L) * (theta);
    final_color +=
        m_specular.f(inter.norm, inter.raydir, light_dir).mul(L) * (theta);
    return final_color;
}
