#ifndef SCENE_H
#define SCENE_H

#include <opencv2/opencv.hpp>
#include <string>
#include "camera.h"
#include "light.h"
#include "object.h"
#include "sample.h"
#include "screen.h"
#include "typedef.h"

class Scene {
   public:
    Scene();
    std::vector<light_ptr>& lights() { return m_lights; }
    std::vector<Object>& objects() { return m_objects; }
    Camera& camera() { return m_camera; }
    Screen& screen() { return m_screen; }
    bool shadow() const{
        return m_shadow;
    }
    void shadow(bool new_shadow){
        m_shadow = new_shadow;
    }

    /**
     *  render the scene to an nxn pixel picture and using sample method method
     */
    img_t render(int n = 200,
                     sample_method method = RT::uniform_sample) const;

   private:
    /**
     *  calculate the first rate light
     */
    arr3 integrate_light(const Ray& ray) const;

    std::vector<light_ptr> m_lights;
    std::vector<Object> m_objects;
    Screen m_screen;
    Camera m_camera;
    bool m_shadow;
};

#endif
