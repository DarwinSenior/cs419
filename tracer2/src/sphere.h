#ifndef SPHERE_H
#define SPHERE_H

#include <opencv2/opencv.hpp>
#include <utility>
#include "geometry.h"
#include "intersect.h"
#include "ray.h"

class Sphere : public Geometry {
   public:
    /**
     *  the sphere is specify by center and its radius
     */
    Sphere(cv::Vec3f pos, float radius);

    bool intersect(const Ray& ray, Intersect& inter) const;

    const cv::Vec3f& center() const { return m_center; }
    float radius() const { return m_radius; }

   private:
    cv::Vec3f m_center;
    float m_radius;
};

#endif
