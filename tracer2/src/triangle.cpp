#include "triangle.h"
#include <limits>

using namespace cv;

Triangle::Triangle(vec3 p1, vec3 p2, vec3 p3){
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
    m_norm =(m_p1-m_p2).cross(m_p1-m_p3).normalized();
}

bool Triangle::intersect(const Ray& ray, Intersect& intersect) const{
    auto d = m_norm.dot(m_p1);
    float dist = (d-ray.o.dot(m_norm))/(ray.d.dot(m_norm));
    auto pos = ray.pos(dist);

    if (dist > 0 && dist < intersect.dist && inside_triange(pos)){
        intersect.norm = m_norm;
        intersect.pos = pos;
        intersect.dist = dist;
        return true;
    }else{
        return false;
    }

}


bool Triangle::inside_triange(const vec3& p) const{
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

vec3 Triangle::center() const{
    return (m_p1+m_p2+m_p3)/3;
}
