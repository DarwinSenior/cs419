#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include <opencv2/opencv.hpp>
#include "light.h"

class PointLight : public Light {
   public:
    PointLight();
    PointLight(float intensity, cv::Vec3f color, cv::Vec3f pos);
    float dist(const Intersect& inter) const;

    cv::Vec3f color() const { return m_color; }
    float intensity() const { return m_intensity; }
    cv::Vec3f pos() const { return m_pos; }

    cv::Vec3f direction(const Intersect& inter) const;
    cv::Vec3f L(const Intersect& inter) const;

   private:
    cv::Vec3f m_pos;
    float m_intensity;
    cv::Vec3f m_color;
};

#endif
