#ifndef DIRECTIONLIGHT_H_
#define DIRECTIONLIGHT_H_

#include <opencv2/opencv.hpp>
#include "light.h"

class DirectionLight: public Light{
public:
    DirectionLight();
    DirectionLight(float intensity, cv::Vec3f color, cv::Vec3f dir);

    cv::Vec3f direction(const Intersect& inter) const;
    cv::Vec3f L(const Intersect& inter) const;
    float dist(const Intersect& inter) const;

    cv::Vec3f color() const{
        return m_color;
    }
    cv::Vec3f dir() const{
        return m_dir;
    }
    float intensity() const{
        return m_intensity;
    }

private:
    cv::Vec3f m_color;
    cv::Vec3f m_dir;
    float m_intensity;
};

#endif
