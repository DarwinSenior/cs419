#ifndef INTERSECT_H
#define INTERSECT_H

#include <opencv2/opencv.hpp>
#include <limits>
#include "ray.h"
#include "typedef.h"

class Material;
struct Intersect {
    vec3 norm;
    vec3 pos;
    vec3 raydir;
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
