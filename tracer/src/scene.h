#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "screen.h"
#include "light.h"
#include <opencv2/opencv.hpp>
#include <string>
#include "object.h"
#include "typedef.h"
#include "sample.h"

class Scene{

public:
    Scene();
    Scene(std::string name);
    std::vector<light_ptr>& lights(){ return m_lights; }
    std::vector<object_ptr>& objects(){ return m_objects; }
    Camera& camera(){ return m_camera; }
    Screen& screen(){ return m_screen; }

    /**
     *  render the scene to an nxn pixel picture and using sample method method
     */
    cv::Mat3f render(int n=200, sample_method method=RT::uniform_sample) const;

private:

    /**
     *  calculate the first rate light
     */
    cv::Vec3f integrate_light(const Ray& ray) const;

    std::vector<light_ptr> m_lights;
    std::vector<object_ptr> m_objects;
    Screen m_screen;
    Camera m_camera;

};

#endif
