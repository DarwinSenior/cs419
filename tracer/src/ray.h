#ifndef RAY_H
#define RAY_H
#include <opencv2/opencv.hpp>

struct Ray{
    cv::Vec3f o; // origin
    cv::Vec3f d; // direction
    cv::Vec3f pos(float dist) const{
        return o+d*dist;
    }
};

#endif
