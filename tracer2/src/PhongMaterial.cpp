#include "PhongMaterial.h"

using namespace std;

namespace {}

PhongMaterial::PhongMaterial(float ks, float kd, float alpha, vec3 colour)
    : m_diffuse(DiffuseBRDF(kd, colour)), m_specular(SpecularBRDF(ks, alpha)){};

arr3 PhongMaterial::shade(const Intersect& inter, const Light& light) {
    arr3 final_color;
    auto light_dir = light.direction(inter);
    auto L = light.L(inter);
    auto theta = max(-light_dir.dot(inter.norm), 0.0f);
    final_color +=
        m_diffuse.f(inter.norm, inter.raydir, light_dir)* L * (theta);
    final_color +=
        m_specular.f(inter.norm, inter.raydir, light_dir) * L * (theta);
    return final_color;
}
