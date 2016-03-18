#ifndef SCREEN_H
#define SCREEN_H

#include <utility>
#include "camera.h"
#include "ray.h"
#include "typedef.h"

/**
 *  standard for size and position
 *  pos[0] -> pos.x pos[1] -> pos.y
 *  size[0] -> size.width size[1] -> size.height
 */
class Screen {
   public:
    Screen(vec2 size, float focus);
    Screen();

    float focus() const { return m_focus; }
    void focus(const float& new_focus) { m_focus = new_focus; }
    size2 size() const { return m_size; }
    void size(const size2& new_size) { m_size = new_size; }
    void set_othorgraphic();
    void shoot_ray(const Camera& camera, const arr2& pos, Ray& ray) const;

   private:
    vec3 ray_pos(const Camera& cam, const arr2& pos) const;
    size2 m_size;
    float m_focus;
};

#endif
