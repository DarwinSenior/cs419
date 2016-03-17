#ifndef LIGHT_H
#define LIGHT_H

#include <opencv2/opencv.hpp>
#include "intersect.h"

class Light {
   public:
    Light() {}
    /**
     *  calculate the intensity specified by intersection
     */
    virtual cv::Vec3f direction(const Intersect& inter) const = 0;
    virtual cv::Vec3f L(const Intersect& inter) const = 0;
    virtual float dist(const Intersect& inter) const = 0;

   protected:
};

#endif
