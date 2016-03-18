#ifndef LIGHT_H
#define LIGHT_H

#include "typedef.h"
#include "intersect.h"

class Light {
   public:
    Light() {}
    /**
     *  calculate the intensity specified by intersection
     */
    virtual vec3 direction(const Intersect& inter) const = 0;
    virtual arr3 L(const Intersect& inter) const = 0;
    virtual float dist(const Intersect& inter) const = 0;

   protected:
};

#endif
