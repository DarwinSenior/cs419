#ifndef INTERSECT_H
#define INTERSECT_H

#include <opencv2/opencv.hpp>
#include <limits>
#include "ray.h"

class Material;
struct Intersect {
    cv::Vec3f norm;
    cv::Vec3f pos;
    cv::Vec3f raydir;
    std::shared_ptr<Material> material;
    float dist;
    float noIntersection() {
        dist = std::numeric_limits<float>::infinity();
        return dist;
    }
    Intersect(const Ray& ray){
        raydir = ray.d;
        noIntersection();
    }
};

Intersect InfiniteIntersect();

#endif
