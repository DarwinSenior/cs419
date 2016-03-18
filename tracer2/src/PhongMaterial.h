#ifndef PHONGMATERIAL_H_
#define PHONGMATERIAL_H_

#include "typedef.h"

#include "ambient_brdf.h"
#include "diffuse_brdf.h"
#include "material.h"
#include "specular_brdf.h"

class PhongMaterial : public Material {
   public:
    PhongMaterial(float ks, float kd, float alpha, vec3 colour);

    arr3 shade(const Intersect& inter, const Light& light);


   private:
    DiffuseBRDF m_diffuse;
    SpecularBRDF m_specular;
};

#endif
