#include "scene.h"
#include "sample.h"

#include <fstream>
#include <utility>
#include "../lib/json.hpp"
#include "PhongMaterial.h"

using namespace std;
using namespace cv;
using namespace RT;
using json = nlohmann::json;
namespace {
float INF = std::numeric_limits<float>::infinity();
float epsilon = 0.001;
bool not_shadowed(const Light& light, const Intersect& inter,
                  const vector<Object>& objects) {
    Ray ray;
    ray.d = -light.direction(inter);
    ray.o = inter.pos + ray.d * epsilon;
    Intersect new_inter(ray);
    for (auto& object : objects) {
        object.intersect(ray, new_inter);
    }

    return (new_inter.dist + epsilon > light.dist(inter));
}
}

Scene::Scene() {
    m_lights = vector<light_ptr>();
    m_objects = vector<Object>();
    m_camera = Camera();
    m_screen = Screen(Size(4, 4), 2.0);
}

Mat3f Scene::render(int n, sample_method method) const {
    Mat3f result = Mat3f(n, n);
    Mat2f samples = method(n);
    Ray ray;
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            float x = samples[i][j][0];
            float y = samples[i][j][1];

            m_screen.shoot_ray(m_camera, x, y, ray);
            result[i][j] = integrate_light(ray);
        }
    }
    return result;
}

Vec3f Scene::integrate_light(const Ray& ray) const {
    auto inter = Intersect(ray);
    for (auto& object : m_objects) {
        object.intersect(ray, inter);
    }
    auto integral = Vec3f();
    if (inter.dist != INF) {
        for (auto& light_ptr : m_lights) {
            if (!m_shadow || not_shadowed(*light_ptr, inter, m_objects)) {
                integral += inter.material->shade(inter, *light_ptr);
            }
        }
    }
    return integral;
}
