#ifndef MATERIAL_H
#define MATERIAL_H
#include <opencv2/opencv.hpp>

struct Material{
    float kd; // diffusive surface
    float ks; // specular surface
    float alpha;
    Material(){
        kd = 1;
        ks = 0;
        alpha = 0;
    }
    cv::Vec3f colour;
};


#endif
