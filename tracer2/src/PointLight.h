#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "typedef.h"
#include "light.h"

class PointLight : public Light {
   public:
    PointLight();
    PointLight(float intensity, arr3 color, vec3 pos);
    float dist(const Intersect& inter) const;

    arr3 color() const { return m_color; }
    float intensity() const { return m_intensity; }
    vec3 pos() const { return m_pos; }

    vec3 direction(const Intersect& inter) const;
    arr3 L(const Intersect& inter) const;

   private:
    vec3 m_pos;
    float m_intensity;
    arr3 m_color;
};

#endif
