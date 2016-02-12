#ifndef SAMPLE_H
#define SAMPLE_H

#include <vector>
#include <opencv2/opencv.hpp>
namespace RT{
    cv::Mat2f uniform_sample(int n);
    cv::Mat2f multi_jittered(int n);
    cv::Mat2f hammersley(int n);
}

#endif
