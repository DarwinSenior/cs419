#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <opencv2/opencv.hpp>
#include "geometry.h"
#include "ray.h"
#include "intersect.h"

class Triangle: public Geometry{
public:
    Triangle(cv::Vec3f p1, cv::Vec3f p2, cv::Vec3f p3);
    void intersect(const Ray& ray, Intersect& intersect) const;

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
