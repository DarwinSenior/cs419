#ifndef SPECULAR_BRDF_H_
#define SPECULAR_BRDF_H_

#include "BRDF.h"
#include "typedef.h"

class SpecularBRDF : public BRDF {
   public:
    SpecularBRDF(float k, float alpha);

    arr3 f(const vec3& n, const vec3& w_i,
                const vec3& w_o) const;

   private:
    const float m_k;
    const float m_alpha;
};

#endif
