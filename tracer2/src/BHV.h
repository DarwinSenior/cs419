#ifndef BHV_H_
#define BHV_H_

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

#include "BHVNode.h"
#include "intersect.h"
#include "ray.h"
#include "geometry.h"

template<class T>
class BHV : public Geometry{
   public:
    BHV(std::vector<T> geos, std::vector<int> indicies);
    BHV(std::vector<T> geos);
    ~BHV();
    bool intersect(const Ray& ray, Intersect& inter) const;
    void print();

   private:
    void build(BHVNode* node, size_t depth);
    void clear();
    void print(BHVNode* node, const std::string& prefix);

    std::vector<T> m_geos;
    std::vector<int> m_indicies;
    BHVNode* m_root;
    size_t MAX_DEPTH = 40;
    size_t MIN_ITEMS = 4;
};

#endif
