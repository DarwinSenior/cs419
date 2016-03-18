#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <opencv2/opencv.hpp>
#include "ray.h"
#include "intersect.h"

class Geometry {
   public:
    virtual bool intersect(const Ray&, Intersect&) const = 0;
   private:
};

#endif
