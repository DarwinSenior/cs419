#include "triangle.h"
#include <limits>

using namespace cv;

Triangle::Triangle(Vec3f p1, Vec3f p2, Vec3f p3){
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
    m_norm = normalize((m_p1-m_p2).cross(m_p1-m_p3));
}

void Triangle::intersect(const Ray& ray, Intersect& intersect) const{
    auto d = m_norm.dot(m_p1);
    float dist = (d-ray.o.dot(m_norm))/(ray.d.dot(m_norm));
    auto pos = ray.pos(dist);

    if (dist > 0 && inside_triange(pos)){
        intersect.norm = m_norm;
        intersect.pos = pos;
        intersect.dist = dist;
    }else{
        intersect.noIntersection();
    }
}


bool Triangle::inside_triange(const Vec3f& p) const{
    auto v1 = m_p2-m_p1;
    auto v2 = m_p3-m_p1;
    auto v3 = p-m_p1;

    auto dot11 = v1.dot(v1);
    auto dot12 = v1.dot(v2);
    auto dot13 = v1.dot(v3);
    auto dot22 = v2.dot(v2);
    auto dot23 = v2.dot(v3);

    float in_denom = 1.0/(dot11*dot22-dot12*dot12);
    float u = (dot22*dot13-dot12*dot23) * in_denom;
    float v = (dot11*dot23-dot12*dot13) * in_denom;

    return (u>=0) && (v>=0) && (u+v<1);
}
