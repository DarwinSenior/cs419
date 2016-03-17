#ifndef MATERIAL_H
#define MATERIAL_H
#include <opencv2/opencv.hpp>
#include "light.h"

struct Intersect;
class Material {
   public:
    virtual cv::Vec3f shade(const Intersect& inter, const Light& light) = 0;

   private:
};


#endif
