#include "camera.h"
#include <cmath>

using namespace std;
using namespace cv;

Camera::Camera(Vec3f up, Vec3f front, Vec3f pos) {
    m_up = normalize(up);
    m_front = normalize(front);
    m_pos = pos;
}

void Camera::move(float v) { m_pos = m_pos + m_front * v; }

void Camera::move(const Vec3f& v) { m_pos = m_pos + v; }

void Camera::pitch(float v) {
    auto right = m_up.cross(m_front);
    right = normalize(cos(v) * right + sin(v) * m_up);
    m_up = m_front.cross(right);
}

void Camera::roll(float v) {
    auto right = m_up.cross(m_front);
    m_front = normalize(cos(v) * m_front + sin(v) * right);
}

void Camera::yaw(float v) {
    auto right = m_up.cross(m_front);
    m_up = normalize(cos(v) * m_up + sin(v) * m_front);
    m_front = right.cross(m_up);
}
