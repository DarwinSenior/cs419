#ifndef SPHERE_H
#define SPHERE_H

#include <utility>
#include "geometry.h"
#include "intersect.h"
#include "ray.h"
#include "typedef.h"

class Sphere : public Geometry {
   public:
    /**
     *  the sphere is specify by center and its radius
     */
    Sphere(vec3 pos, float radius);

    bool intersect(const Ray& ray, Intersect& inter) const;

    const vec3& center() const { return m_center; }
    float radius() const { return m_radius; }

   private:
    vec3 m_center;
    float m_radius;
};

#endif
