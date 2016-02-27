#ifndef SPHERE_H
#define SPHERE_H

#include <opencv2/opencv.hpp>
#include "geometry.h"
#include "ray.h"
#include "intersect.h"
#include <utility>

class Sphere : public Geometry {
   public:
    /**
     *  the sphere is specify by center and its radius
     */
    Sphere(cv::Vec3f pos, float radius);

    void intersect(const Ray& ray, Intersect& inter) const;

   private:
    cv::Vec3f m_center;
    float m_radius;
};

#endif
