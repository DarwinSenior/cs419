#include "screen.h"

using namespace std;
using namespace cv;

namespace{
    float inf = numeric_limits<float>::infinity();
}

Screen::Screen(Size2f size, float focus){
    m_size = size;
    m_focus = focus;
}

void Screen::set_othorgraphic(){
    m_focus = inf;
}

void Screen::shoot_ray(const Camera& cam, float x, float y, Ray& ray) const{
    shoot_ray(cam, Point2f(x, y), ray);
}

void Screen::shoot_ray(const Camera& cam, const Point2f& pos, Ray& ray) const{
    ray.o = ray_pos(cam, pos);
    if (m_focus == inf){
        ray.d = cam.front();
    }else{
        ray.d = normalize(ray.o-cam.pos()+m_focus*cam.front());
    }
}

Vec3f Screen::ray_pos(const Camera& cam, Point2f pos) const{
    auto x = pos.x-.5;
    auto y = pos.y-.5;
    auto dx = cam.up().cross(cam.front());
    auto dy = cam.up();
    return cam.pos()+x*m_size.width*dx+y*m_size.height*dy;
}
