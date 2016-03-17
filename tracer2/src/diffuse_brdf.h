#ifndef DIFFUSE_BRDF_H_
#define DIFFUSE_BRDF_H_

#include <opencv2/opencv.hpp>
#include "BRDF.h"

class DiffuseBRDF : public BRDF {
   public:
    DiffuseBRDF(float k, cv::Vec3f colour);

    cv::Vec3f f(const cv::Vec3f& n, const cv::Vec3f& w_i,
                const cv::Vec3f& w_o) const;

   private:
    const float m_k;
    const cv::Vec3f m_colour;
};

#endif
