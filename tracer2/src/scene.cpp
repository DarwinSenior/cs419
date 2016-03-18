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

    return (new_inter.dist + epsilon >= light.dist(inter));
}
}

Scene::Scene() {
    m_lights = vector<light_ptr>();
    m_objects = vector<Object>();
    m_camera = Camera();
    m_screen = Screen(vec2(4, 4), 2.0);
}

img_t Scene::render(int n, sample_method method) const {
    img_t result = img_t(n, n);
    sample_t samples = method(n);
    Ray ray;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            m_screen.shoot_ray(m_camera, samples(y, x), ray);
            result(y, x) = integrate_light(ray);
        }
    }
    return result;
}

arr3 Scene::integrate_light(const Ray& ray) const {
    auto inter = Intersect(ray);
    for (auto& object : m_objects) {
        object.intersect(ray, inter);
    }
    auto integral = arr3();
    if (inter.dist != INF) {
        for (auto& light_ptr : m_lights) {
            if (!m_shadow || not_shadowed(*light_ptr, inter, m_objects)) {
                integral = integral + inter.material->shade(inter, *light_ptr);
            }
        }
    }
    return integral;
}
