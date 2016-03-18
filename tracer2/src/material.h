#ifndef MATERIAL_H
#define MATERIAL_H
#include "typedef.h"
#include "light.h"

struct Intersect;
class Material {
   public:
    virtual arr3 shade(const Intersect& inter, const Light& light) = 0;

   private:
};


#endif
