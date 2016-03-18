#include "screen.h"

using namespace std;

namespace {
float inf = numeric_limits<float>::infinity();
}

Screen::Screen(vec2 size, float focus) {
    m_size = size;
    m_focus = focus;
}

Screen::Screen() : Screen(vec2(4, 4), 1) {}

void Screen::set_othorgraphic() { m_focus = inf; }

void Screen::shoot_ray(const Camera& cam, const arr2& pos, Ray& ray) const {
    ray.o = ray_pos(cam, pos);
    if (m_focus == inf) {
        ray.d = cam.front();
    } else {
        ray.d = (ray.o - cam.pos() + m_focus * cam.front()).normalized();
    }
}

vec3 Screen::ray_pos(const Camera& cam, const arr2& pos) const {

    auto pos_scale = (pos - 0.5) * m_size;
    auto dx = cam.up().cross(cam.front());
    auto dy = cam.up();

    return cam.pos() + pos_scale[0] * dx + pos_scale[1] * dy;
}
