#include "camera.h"
#include <cmath>

using namespace std;

Camera::Camera(vec3 up, vec3 front, vec3 pos) {
    m_up = up.normalized();
    m_front = (front).normalized();
    m_pos = pos;
}

void Camera::move(float v) { m_pos = m_pos + m_front * v; }

void Camera::move(const vec3& v) { m_pos = m_pos + v; }

void Camera::pitch(float v) {
    auto right = m_up.cross(m_front);
    right = (cos(v) * right + sin(v) * m_up).normalized();
    m_up = m_front.cross(right);
}

void Camera::roll(float v) {
    auto right = m_up.cross(m_front);
    m_front = (cos(v) * m_front + sin(v) * right).normalized();
}

void Camera::yaw(float v) {
    auto right = m_up.cross(m_front);
    m_up = (cos(v) * m_up + sin(v) * m_front).normalized();
    m_front = right.cross(m_up);
}
