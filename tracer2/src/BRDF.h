#ifndef BRDF_H_
#define BRDF_H_

#include <opencv2/opencv.hpp>
#include "intersect.h"

class BRDF {
   public:
    virtual cv::Vec3f f(const cv::Vec3f& p, const cv::Vec3f& w_i,
                        const cv::Vec3f& w_o) const = 0;
   private:
};

#endif
