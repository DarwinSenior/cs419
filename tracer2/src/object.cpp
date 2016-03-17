#include "object.h"

Object::Object(geo_ptr geometry, mat_ptr material)
    : m_geometry(geometry), m_material(material) {}

bool Object::intersect(const Ray& ray, Intersect& inter) const{
    bool updated = m_geometry->intersect(ray, inter);
    if (updated){
        inter.material = m_material;
    }
    return updated;
}
