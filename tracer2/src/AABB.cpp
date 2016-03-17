#include "AABB.h"

#include <limits>

using namespace cv;
using namespace std;

/**
 *  this function enaures that the linking is done.
 */
void AABB_CODE_GENERATOR() {
    vector<Triangle> tris;
    vector<Sphere> sphs;
    vector<int> idxs;
    AABB e(idxs.begin(), idxs.end(), tris);
    AABB f(idxs.begin(), idxs.end(), tris);
    AABB a(idxs, tris);
    AABB b(idxs, sphs);
    AABB c(tris);
    AABB d(sphs);
}
namespace {
using idx_t = std::vector<int>::const_iterator;
float INF = std::numeric_limits<float>::infinity();
void maximum_update(Vec3f& max_vec, const Vec3f& v) {
    max_vec[0] = std::max(v[0], max_vec[0]);
    max_vec[1] = std::max(v[1], max_vec[1]);
    max_vec[2] = std::max(v[2], max_vec[2]);
}

void minimum_update(Vec3f& min_vec, const Vec3f& v) {
    min_vec[0] = std::min(v[0], min_vec[0]);
    min_vec[1] = std::min(v[1], min_vec[1]);
    min_vec[2] = std::min(v[2], min_vec[2]);
}

Vec3f maximum(const vector<Vec3f>& vecs) {
    auto max_vec = Vec3f();
    max_vec = vecs[0];
    for (auto& v : vecs) {
        maximum_update(max_vec, v);
    }
    return max_vec;
}

void maximum_update(Vec3f& v, const Triangle& triangle) {
    maximum_update(v, triangle.p1());
    maximum_update(v, triangle.p2());
    maximum_update(v, triangle.p3());
}

void maximum_update(Vec3f& v, const Sphere& sphere) {
    float r = sphere.radius();
    maximum_update(v, sphere.center() + Vec3f(r, r, r));
}

void minimum_update(Vec3f& v, const Triangle& triangle) {
    minimum_update(v, triangle.p1());
    minimum_update(v, triangle.p2());
    minimum_update(v, triangle.p3());
}
void minimum_update(Vec3f& v, const Sphere& sphere) {
    float r = sphere.radius();
    minimum_update(v, sphere.center() - Vec3f(r, r, r));
}

template <class T>
Vec3f maximum(const vector<T>& geos, const idx_t begin, const idx_t end) {
    auto max_vec = Vec3f(-INF, -INF, -INF);
    for (auto idx = begin; idx < end; idx++) {
        maximum_update(max_vec, geos[*idx]);
    }
    return max_vec;
}

template <class T>
Vec3f maximum(const vector<T>& vecs) {
    auto max_vec = Vec3f(-INF, -INF, -INF);
    for (auto& geo : vecs) {
        maximum_update(max_vec, geo);
    }
    return max_vec;
}

template <class T>
Vec3f minimum(const vector<T>& geos, idx_t begin, idx_t end) {
    auto min_vec = Vec3f(INF, INF, INF);
    for (auto idx = begin; idx < end; idx++) {
        minimum_update(min_vec, geos[*idx]);
    }
    return min_vec;
}

template <class T>
Vec3f minimum(const vector<T>& vecs) {
    auto min_vec = Vec3f(INF, INF, INF);
    for (auto& v : vecs) {
        minimum_update(min_vec, v);
    }
    return min_vec;
}
}

AABB::AABB(const Vec3f min, const Vec3f max) {
    m_max = max;
    m_min = min;
}

AABB::AABB(const AABB& other) {
    m_max = other.m_max;
    m_min = other.m_min;
}

template <class T>
AABB::AABB(const vector<T>& verties) {
    m_min = minimum(verties);
    m_max = maximum(verties);
}


template <class T>
AABB::AABB(const idx_t begin, const idx_t end, const vector<T>& verties) {
    m_min = minimum(verties, begin, end);
    m_max = maximum(verties, begin, end);
}

template <class T>
AABB::AABB(const vector<int>& indicies, const vector<T>& verties)
    : AABB(indicies.begin(), indicies.end(), verties) {
    }

AABB::AABB() {
    m_min = Vec3f(-INF, -INF, -INF);
    m_max = Vec3f(INF, INF, INF);
}

float AABB::volume() {
    auto diff = m_max - m_min;
    return diff[0] * diff[1] * diff[2];
}

Vec3f AABB::center() { return (m_max + m_min) / 2; }

float AABB::surface_area() {
    auto diff = m_max - m_min;
    return (diff[0] * diff[1] + diff[0] * diff[2] + diff[1] * diff[2]) * 2;
}

bool AABB::inside(Vec3f point) {
    return (point[0] < m_max[0]) && (point[1] < m_max[1]) &&
           (point[2] < m_max[2]) && (point[0] > m_min[0]) &&
           (point[1] > m_min[1]) && (point[2] > m_min[2]);
}

// http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
float AABB::intersect(const Ray& ray) {
    Vec3f min_x = Vec3f((m_min[0] - ray.o[0]) / ray.d[0],
                        (m_min[1] - ray.o[1]) / ray.d[1],
                        (m_min[2] - ray.o[2]) / ray.d[2]);

    Vec3f max_x = Vec3f((m_max[0] - ray.o[0]) / ray.d[0],
                        (m_max[1] - ray.o[1]) / ray.d[1],
                        (m_max[2] - ray.o[2]) / ray.d[2]);

    float tmin = max(max(min(min_x[0], max_x[0]), min(min_x[1], max_x[1])),
                     min(min_x[2], max_x[2]));
    float tmax = min(min(max(min_x[0], max_x[0]), max(min_x[1], max_x[1])),
                     max(min_x[2], max_x[2]));

    if (tmax < 0) {
        return INF;
    } else {
        return tmin > tmax ? INF : tmin;
    }
}
