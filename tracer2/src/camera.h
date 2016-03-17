#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/opencv.hpp>

class Camera {
   public:
    Camera(cv::Vec3f up, cv::Vec3f front, cv::Vec3f pos);
    Camera() {
        m_up = cv::Vec3f(0, 1, 0);
        m_pos = cv::Vec3f(0, 0, 0);
        m_front = cv::Vec3f(0, 0, 1);
    }
    void move(float amount);
    void move(const cv::Vec3f& amount);
    void pitch(float amount);
    void yaw(float amount);
    void roll(float amount);

    cv::Vec3f front() const { return m_front; }
    cv::Vec3f up() const { return m_up; }
    cv::Vec3f pos() const { return m_pos; }

   private:
    cv::Vec3f m_up;
    cv::Vec3f m_front;
    cv::Vec3f m_pos;
};

#endif
