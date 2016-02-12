#include "scene.h"
#include "sample.h"

#include <utility>
#include <fstream>
#include "../lib/json.hpp"

using namespace std;
using namespace cv;
using namespace RT;
using json = nlohmann::json;
namespace{
    Vec3f parse_vector(json data){
        return Vec3f((float)data[0], (float)data[1], (float)data[2]);
    }
    Camera parse_camera(json data){
        if (!data.is_object()) return Camera();
        auto up = parse_vector(data["up"]);
        auto front = parse_vector(data["front"]);
        auto pos = parse_vector(data["pos"]);
        return Camera(up, front, pos);
    }
    Screen parse_screen(json data){
        if (!data.is_object()) return Screen();
        auto size = Size2f(data["size"][0], data["size"][1]);
        float focus = data["focus"];
        return Screen(size, focus);
    }
    object_ptr parse_object(json data);
    // vector<object_ptr> parse_objects(json data){
    //     auto objs = vector<object_ptr>();
    //     if (!data.is_array()) return objs;
    //     for (auto& obj_data : data){
    //         auto obj = parse_objects(obj_data);
    //         objs.push_back(move(obj));
    //     }
    //     return objs;
    // }

}

Scene::Scene(){
    m_lights = vector<light_ptr>();
    m_objects = vector<object_ptr>();
    m_camera = Camera();
    m_screen = Screen(Size(4, 4), 2.0);
}

Scene::Scene(std::string name){
    fstream inputfile(name);
    auto data = json();
    data << inputfile;
    m_camera = parse_camera(data["camera"]);
    m_screen = parse_screen(data["screen"]);
    m_lights = vector<light_ptr>();
    m_objects = vector<object_ptr>();
    // m_objects = parse_objects(data["objects"]);
    // m_lights = parse_objects(data["lights"]);
}

Mat3f Scene::render(int n, sample_method method) const{
    Mat3f result = Mat3f(n,n);
    Mat2f samples = method(n);
    Ray ray;
    for (int i=0; i<result.rows; i++){
        for (int j=0; j<result.cols; j++){
            float x = samples[i][j][0];
            float y = samples[i][j][1];

            m_screen.shoot_ray(m_camera, x, y, ray);
            result[i][j] = integrate_light(ray);
        }
    }
    return result;
}

Vec3f Scene::integrate_light(const Ray& ray) const{

    auto inter = Intersect();
    inter.noIntersection();
    inter.raydir = ray.d;
    for (auto& object: m_objects){
        object->updateIntersection(ray, inter);
    }
    auto integral = Vec3f();
    if (inter.dist != numeric_limits<float>::infinity()){
        for (auto& light: m_lights){
            float i = light->intensity(inter);
            integral = integral+i*inter.material.colour;
        }
    }
    return integral;
}

