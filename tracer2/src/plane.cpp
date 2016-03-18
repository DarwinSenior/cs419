#include "plane.h"

using namespace std;
using namespace cv;

Plane::Plane(vec3 norm, float dist) {
    m_norm = norm.normalized();
    m_dist = dist;
}

bool Plane::intersect(const Ray& ray, Intersect& inter) const {
    float dist = (m_dist - ray.o.dot(m_norm)) / ray.d.dot(m_norm);
    if (dist > 0 && dist < inter.dist) {
        inter.dist = dist;
        inter.norm = m_norm;
        inter.pos = ray.pos(dist);
        return true;
    } else {
        return false;
    }
}
