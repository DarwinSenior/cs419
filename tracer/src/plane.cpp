#include "plane.h"

using namespace std;
using namespace cv;

Plane::Plane(Vec3f norm, float dist){
    m_norm = normalize(norm);
    m_dist = dist;
}

void Plane::intersect(const Ray& ray, Intersect& inter) const{
    float dist = (m_dist-ray.o.dot(m_norm)) / ray.o.dot(m_norm);
    if (dist > 0){
        inter.dist = dist;
        inter.norm = m_norm;
        inter.pos = ray.pos(dist);
    }else{
        inter.noIntersection();
    }
}
