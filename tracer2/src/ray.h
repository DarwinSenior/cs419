#ifndef RAY_H
#define RAY_H
#include "typedef.h"

struct Ray{
    vec3 o; // origin
    vec3 d; // direction
    vec3 pos(float dist) const{
        return o+d*dist;
    }
};

#endif
