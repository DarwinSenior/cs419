#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <opencv2/opencv.hpp>
#include "ray.h"
#include "intersect.h"

class Geometry {
   public:
    virtual void intersect(const Ray&, Intersect&) const = 0;
    /**
     *  the update function takes the ray and calculate intersection
     *  it will update the intersection if the ray hits its object with nearer
     * distance
     */
    void update(const Ray& ray, Intersect& inter) const {
        auto new_inter = Intersect();
        intersect(ray, new_inter);
        if (inter.dist < new_inter.dist) {
            inter = new_inter;
        }
    }
};

#endif
