#ifndef AABB_H_
#define AABB_H_

#include <opencv2/opencv.hpp>
#include <vector>

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
    AABB(const cv::Vec3f min, const cv::Vec3f max);
    AABB(const AABB& other);

    const cv::Vec3f& min_p() const { return m_min; }
    const cv::Vec3f& max_p() const { return m_max; }

    cv::Vec3f center();
    float volume();
    float surface_area();
    bool inside(cv::Vec3f point);
    float intersect(const Ray& ray);

   private:
    cv::Vec3f m_min;
    cv::Vec3f m_max;
};

#endif
