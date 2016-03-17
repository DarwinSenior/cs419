#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <opencv2/opencv.hpp>
#include "geometry.h"
#include "intersect.h"
#include "ray.h"

class Triangle : public Geometry {
   public:
    Triangle(cv::Vec3f p1, cv::Vec3f p2, cv::Vec3f p3);
    bool intersect(const Ray& ray, Intersect& intersect) const;

    const cv::Vec3f& p1() const { return m_p1; }
    const cv::Vec3f& p2() const { return m_p2; }
    const cv::Vec3f& p3() const { return m_p3; }

    cv::Vec3f center() const;

   private:
    /*
     * return if p is inside the triangle
     * #419begin #type=3 src-http://www.blackpawn.com/texts/pointinpoly/
     */
    bool inside_triange(const cv::Vec3f& p) const;

    cv::Vec3f m_p1;
    cv::Vec3f m_p2;
    cv::Vec3f m_p3;
    cv::Vec3f m_norm;
};

#endif
