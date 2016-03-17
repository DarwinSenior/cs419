#include "sphere.h"
#include <cmath>
#include <utility>

using namespace cv;
using namespace std;

namespace {
float INF = numeric_limits<float>::infinity();
pair<float, float> solve(float a, float b, float c) {
    float delta = b * b - 4 * a * c;
    if (delta < 0) {
        return make_pair(INF, INF);
    } else {
        float sd = sqrt(delta);  // delta^(1/2)
        return make_pair((-b - sd) / (2 * a), (-b + sd) / (2 * a));
    }
}
}

Sphere::Sphere(Vec3f pos, float radius) {
    m_center = pos;
    m_radius = radius;
}

bool Sphere::intersect(const Ray& ray, Intersect& inter) const {
    float a = ray.d.dot(ray.d);
    auto oc = ray.o - m_center;
    float b = 2 * ray.d.dot(oc);
    float c = oc.dot(oc) - m_radius * m_radius;
    auto solution = solve(a, b, c);
    float finial_dist = INF;
    if (solution.first > 0) {
        finial_dist = solution.first;
    } else if (solution.second > 0) {
        finial_dist = solution.second;
    }
    if (finial_dist < inter.dist) {
        inter.dist = finial_dist;
        inter.pos = ray.pos(inter.dist);
        inter.norm = normalize(inter.pos - m_center);
        return true;
    }else{
        return false;
    }
}
