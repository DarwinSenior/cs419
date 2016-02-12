#ifndef SCREEN_H
#define SCREEN_H

#include <opencv2/opencv.hpp>
#include <utility>
#include "camera.h"
#include "ray.h"

class Screen{
public:
    Screen(cv::Size2f size, float focus);
    Screen(){
        m_size = cv::Size(4, 4);
        m_focus = 1;
    }

    float focus() const { return m_focus; }
    cv::Size size() const { return m_size; }
    void set_othorgraphic();
    void shoot_ray(const Camera& camera, const cv::Point2f& pos, Ray& ray) const;
    void shoot_ray(const Camera& camera, float x, float y, Ray& ray) const;


private:
    cv::Vec3f ray_pos(const Camera& cam, cv::Point2f pos) const;
    cv::Size2f m_size;
    float m_focus;
};


#endif
