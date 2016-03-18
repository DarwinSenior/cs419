#ifndef CAMERA_H
#define CAMERA_H

#include "typedef.h"

class Camera {
   public:
    Camera(vec3 up, vec3 front, vec3 pos);
    Camera() {
        m_up = vec3(0, 1, 0);
        m_pos = vec3(0, 0, 0);
        m_front = vec3(0, 0, 1);
    }
    void move(float amount);
    void move(const vec3& amount);
    void pitch(float amount);
    void yaw(float amount);
    void roll(float amount);

    vec3 front() const { return m_front; }
    vec3 up() const { return m_up; }
    vec3 pos() const { return m_pos; }

   private:
    vec3 m_up;
    vec3 m_front;
    vec3 m_pos;
};

#endif
