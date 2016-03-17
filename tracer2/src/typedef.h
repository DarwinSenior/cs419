#ifndef TYPE_DEF_H
#define TYPE_DEF_H

#include <memory>
#include "material.h"
#include "geometry.h"
#include "light.h"
#include <opencv2/opencv.hpp>

using geo_ptr = std::shared_ptr<Geometry>;
using mat_ptr = std::shared_ptr<Material>;
using light_ptr = std::shared_ptr<Light>;

typedef cv::Mat2f (*sample_method)(int);


#endif
