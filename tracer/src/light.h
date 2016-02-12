#ifndef LIGHT_H
#define LIGHT_H

#include <opencv2/opencv.hpp>
#include "intersect.h"

class Light{
public:
    Light(){}
    /**
     *  calculate the intensity specified by intersection
     */
    float virtual intensity(const Intersect& inter) = 0;
};


#endif
