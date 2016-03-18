#include "AABB.h"

#include <limits>

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
const vec3 unbound(INF, INF, INF);

void maximum_update(vec3& max_vec, const vec3& v) {
    max_vec = max_vec.cwiseMax(v);
}

void minimum_update(vec3& min_vec, const vec3& v) {
    min_vec = min_vec.cwiseMin(v);
}

vec3 maximum(const vector<vec3>& vecs) {
    auto max_vec = vec3();
    max_vec = vecs[0];
    for (auto& v : vecs) {
        maximum_update(max_vec, v);
    }
    return max_vec;
}

void maximum_update(vec3& v, const Triangle& triangle) {
    maximum_update(v, triangle.p1());
    maximum_update(v, triangle.p2());
    maximum_update(v, triangle.p3());
}

void maximum_update(vec3& v, const Sphere& sphere) {
    float r = sphere.radius();
    maximum_update(v, sphere.center() + vec3(r, r, r));
}

void minimum_update(vec3& v, const Triangle& triangle) {
    minimum_update(v, triangle.p1());
    minimum_update(v, triangle.p2());
    minimum_update(v, triangle.p3());
}
void minimum_update(vec3& v, const Sphere& sphere) {
    float r = sphere.radius();
    minimum_update(v, sphere.center() - vec3(r, r, r));
}

template <class T>
vec3 maximum(const vector<T>& geos, const idx_t begin, const idx_t end) {
    vec3 max_vec = -unbound;
    for (auto idx = begin; idx < end; idx++) {
        maximum_update(max_vec, geos[*idx]);
    }
    return max_vec;
}

template <class T>
vec3 maximum(const vector<T>& vecs) {
    vec3 max_vec = -unbound;
    for (auto& geo : vecs) {
        maximum_update(max_vec, geo);
    }
    return max_vec;
}

template <class T>
vec3 minimum(const vector<T>& geos, idx_t begin, idx_t end) {
    vec3 min_vec = unbound;
    for (auto idx = begin; idx < end; idx++) {
        minimum_update(min_vec, geos[*idx]);
    }
    return min_vec;
}

template <class T>
vec3 minimum(const vector<T>& vecs) {
    vec3 min_vec = unbound;
    for (auto& v : vecs) {
        minimum_update(min_vec, v);
    }
    return min_vec;
}
}

AABB::AABB(const vec3 min, const vec3 max) {
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
    : AABB(indicies.begin(), indicies.end(), verties) {}

AABB::AABB() {
    m_min = -unbound;
    m_max = unbound;
}

float AABB::volume() {
    auto diff = m_max - m_min;
    return diff[0] * diff[1] * diff[2];
}

vec3 AABB::center() { return (m_max + m_min) / 2; }

float AABB::surface_area() {
    auto diff = m_max - m_min;
    return (diff[0] * diff[1] + diff[0] * diff[2] + diff[1] * diff[2]) * 2;
}

bool AABB::inside(vec3 point) {
    return (point[0] < m_max[0]) && (point[1] < m_max[1]) &&
           (point[2] < m_max[2]) && (point[0] > m_min[0]) &&
           (point[1] > m_min[1]) && (point[2] > m_min[2]);
}

// http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms

float AABB::intersect(const Ray& ray) {
    vec3 min_x = (m_min - ray.o).cwiseQuotient(ray.d);
    vec3 max_x = (m_max - ray.o).cwiseQuotient(ray.d);
    float tmin = min_x.cwiseMin(max_x).maxCoeff();
    float tmax = min_x.cwiseMax(max_x).minCoeff();

    if (tmax < 0) {
        return INF;
    } else {
        return tmin > tmax ? INF : tmin;
    }
}
