#ifndef INTERSECT_H
#define INTERSECT_H

#include <opencv2/opencv.hpp>
#include <limits>
#include "material.h"

struct Intersect{
    cv::Vec3f norm;
    cv::Vec3f pos;
    cv::Vec3f raydir;
    Material material;
    float dist;
    float noIntersection(){
        dist = std::numeric_limits<float>::infinity();
        return dist;
    }
};

Intersect InfiniteIntersect();

#endif
