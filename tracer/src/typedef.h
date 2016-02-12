#ifndef TYPE_DEF_H
#define TYPE_DEF_H

#include <memory>
#include "light.h"
#include "object.h"
#include <opencv2/opencv.hpp>

typedef std::unique_ptr<Light> light_ptr;
typedef std::unique_ptr<Object> object_ptr;
typedef cv::Mat2f (*sample_method)(int);

#endif
