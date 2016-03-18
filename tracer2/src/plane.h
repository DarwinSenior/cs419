#ifndef PLANE_H
#define PLANE_H

#include "geometry.h"
#include "ray.h"
#include "intersect.h"
#include <utility>
#include "typedef.h"

class Plane: public Geometry{
public:
    /**
     * plane is represented by a normal and the distance the plane is to the center
     */
    Plane(vec3 norm, float dist);

    bool intersect(const Ray& ray, Intersect& inter) const;

private:
    vec3 m_norm;
    float m_dist;
};

#endif
