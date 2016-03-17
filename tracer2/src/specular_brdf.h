#ifndef SPECULAR_BRDF_H_
#define SPECULAR_BRDF_H_

#include <opencv2/opencv.hpp>
#include "BRDF.h"

class SpecularBRDF : public BRDF {
   public:
    SpecularBRDF(float k, float alpha);

    cv::Vec3f f(const cv::Vec3f& n, const cv::Vec3f& w_i,
                const cv::Vec3f& w_o) const;

   private:
    const float m_k;
    const float m_alpha;
};

#endif
