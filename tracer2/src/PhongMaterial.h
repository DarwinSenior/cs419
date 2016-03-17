#ifndef PHONGMATERIAL_H_
#define PHONGMATERIAL_H_

#include <opencv2/opencv.hpp>

#include "ambient_brdf.h"
#include "diffuse_brdf.h"
#include "material.h"
#include "specular_brdf.h"

class PhongMaterial : public Material {
   public:
    PhongMaterial(float ks, float kd, float alpha, cv::Vec3f colour);

    cv::Vec3f shade(const Intersect& inter, const Light& light);


   private:
    DiffuseBRDF m_diffuse;
    SpecularBRDF m_specular;
};

#endif
