#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "geometry.h"
#include "intersect.h"
#include "ray.h"
#include "typedef.h"

class Triangle : public Geometry {
   public:
    Triangle(vec3 p1, vec3 p2, vec3 p3);
    bool intersect(const Ray& ray, Intersect& intersect) const;

    const vec3& p1() const { return m_p1; }
    const vec3& p2() const { return m_p2; }
    const vec3& p3() const { return m_p3; }

    vec3 center() const;

   private:
    /*
     * return if p is inside the triangle
     * #419begin #type=3 src-http://www.blackpawn.com/texts/pointinpoly/
     */
    bool inside_triange(const vec3& p) const;

    vec3 m_p1;
    vec3 m_p2;
    vec3 m_p3;
    vec3 m_norm;
};

#endif
