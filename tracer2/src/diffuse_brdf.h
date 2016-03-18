#ifndef DIFFUSE_BRDF_H_
#define DIFFUSE_BRDF_H_

#include "BRDF.h"
#include "typedef.h"

class DiffuseBRDF : public BRDF {
   public:
    DiffuseBRDF(float k, arr3 colour);

    arr3 f(const vec3& n, const vec3& w_i,
                const vec3& w_o) const;

   private:
    const float m_k;
    const arr3 m_colour;
};

#endif
