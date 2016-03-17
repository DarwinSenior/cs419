#ifndef AMBIENT_LIGHT_H_
#define AMBIENT_LIGHT_H_

#include <opencv2/opencv.hpp>
#include "intersect.h"
#include "light.h"

class AmbientLight : public Light {
   public:
    AmbientLight();
    AmbientLight(float intensity, cv::Vec3f color);
    cv::Vec3f direction(const Intersect& inter) const;
    cv::Vec3f L(const Intersect& inter) const;
    float dist(const Intersect& inter) const;

    float intensity() const { return m_intensity; }
    cv::Vec3f color() const { return m_color; }

   private:
    float m_intensity;
    cv::Vec3f m_color;
};

#endif
