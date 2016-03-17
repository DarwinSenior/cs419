#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "geometry.h"
#include "typedef.h"
#include "intersect.h"
#include "ray.h"

class Object{
public:
    Object(geo_ptr geometry, mat_ptr material);
    bool intersect(const Ray& ray, Intersect& inter) const;
private:
    geo_ptr m_geometry;
    mat_ptr m_material;

};

#endif
