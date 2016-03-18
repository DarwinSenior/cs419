#ifndef TYPE_DEF_H
#define TYPE_DEF_H


#include <memory>
#include <opencv2/opencv.hpp>
#include <Eigen3/Eigen/Eigen>

class Geometry;
class Material;
class Light;

using geo_ptr = std::shared_ptr<Geometry>;
using mat_ptr = std::shared_ptr<Material>;
using light_ptr = std::shared_ptr<Light>;
using vec3 = Eigen::Vector3f;
using vec2 = Eigen::Vector2f;
using arr2 = Eigen::Array2f;
using arr3 = Eigen::Array3f;
using size2 = Eigen::Array2f;
using img_t = Eigen::Array<arr3, Eigen::Dynamic, Eigen::Dynamic>;
using sample_t = Eigen::Array<Eigen::Array2f, Eigen::Dynamic, Eigen::Dynamic>;
const float INF = std::numeric_limits<float>::infinity();

typedef sample_t (*sample_method)(int);


#endif
