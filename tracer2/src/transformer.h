#ifndef TRASFORMER_H_
#define TRASFORMER_H_

#include <opencv2/opencv.hpp>

class Transformer{
public:
    Transformer();
    Transformer& identity();
    Transformer& scale(float amount);
    Transformer& scale(float x, float y, float z);
    Transformer& rotate(int axis, float theta);
    Transformer& rotate(float theta1, float phi1);
    Transformer& transit(float x, float y, float z);
    Transformer& transit(int axis, float x);

private:
    cv::Matx44f m_scalar;
    cv::Matx44f m_rotate;
};

#endif
