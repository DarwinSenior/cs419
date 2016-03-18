#ifndef AABB_H_
#define AABB_H_

#include <vector>
#include "typedef.h"

#include "ray.h"
#include "sphere.h"
#include "triangle.h"

class AABB {
   public:
    template <class T>
    AABB(const std::vector<T>& verties);
    template <class T>
    AABB(const std::vector<int>& indicies, const std::vector<T>& verties);
    template <class T>
    AABB(const std::vector<int>::const_iterator begin,
         const std::vector<int>::const_iterator end,
         const std::vector<T>& verties);
    AABB();
    AABB(const vec3 min, const vec3 max);
    AABB(const AABB& other);

    const vec3& min_p() const { return m_min; }
    const vec3& max_p() const { return m_max; }

    vec3 center();
    float volume();
    float surface_area();
    bool inside(vec3 point);
    float intersect(const Ray& ray);

   private:
    vec3 m_min;
    vec3 m_max;
};

#endif
