#ifndef PLANE_H
#define PLANE_H

#include <opencv2/opencv.hpp>
#include "geometry.h"
#include "ray.h"
#include "intersect.h"
#include <utility>

class Plane: public Geometry{
public:
    /**
     * plane is represented by a normal and the distance the plane is to the center
     */
    Plane(cv::Vec3f norm, float dist);

    void intersect(const Ray& ray, Intersect& inter) const;

private:
    cv::Vec3f m_norm;
    float m_dist;
};

#endif
