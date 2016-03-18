#ifndef DIRECTIONLIGHT_H_
#define DIRECTIONLIGHT_H_

#include "typedef.h"
#include "light.h"

class DirectionLight: public Light{
public:
    DirectionLight();
    DirectionLight(float intensity, arr3 color, vec3 dir);

    vec3 direction(const Intersect& inter) const;
    arr3 L(const Intersect& inter) const;
    float dist(const Intersect& inter) const;

    arr3 color() const{
        return m_color;
    }
    vec3 dir() const{
        return m_dir;
    }
    float intensity() const{
        return m_intensity;
    }

private:
    arr3 m_color;
    vec3 m_dir;
    float m_intensity;
};

#endif
