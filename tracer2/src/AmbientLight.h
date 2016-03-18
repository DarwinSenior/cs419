#ifndef AMBIENT_LIGHT_H_
#define AMBIENT_LIGHT_H_

#include "typedef.h"
#include "intersect.h"
#include "light.h"

class AmbientLight : public Light {
   public:
    AmbientLight();
    AmbientLight(float intensity, arr3 color);
    vec3 direction(const Intersect& inter) const;
    arr3 L(const Intersect& inter) const;
    float dist(const Intersect& inter) const;

    float intensity() const { return m_intensity; }
    arr3 color() const { return m_color; }

   private:
    float m_intensity;
    arr3 m_color;
};

#endif
