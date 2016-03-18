#ifndef BRDF_H_
#define BRDF_H_

#include "intersect.h"
#include "typedef.h"

class BRDF {
   public:
    virtual arr3 f(const vec3& p, const vec3& w_i,
                        const vec3& w_o) const = 0;
   private:
};

#endif
