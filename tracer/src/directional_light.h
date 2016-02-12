#ifndef DIR_LIHGHT_H
#define DIR_LIHGHT_H

#include <opencv2/opencv.hpp>
#include "light.h"


class DirLight: public Light{
public:
    DirLight(cv::Vec3f dir, float i);
    float intensity(const Intersect& inter);
    float i(){ return m_i; }
private:
    cv::Vec3f m_dir; // directional light
    float m_i; // intensity
};


#endif
