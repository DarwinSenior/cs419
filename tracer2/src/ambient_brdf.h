#ifndef AMBIENT_BRDF_H_
#define AMBIENT_BRDF_H_

#include <opencv2/opencv.hpp>
#include "BRDF.h"
#include "typedef.h"

class AmbientBRDF : public BRDF {
   public:
    AmbientBRDF(float k, arr3 colour);

    arr3 f(const vec3& n, const vec3& w_i,
                const vec3& w_o) const;

   private:
    const float m_k;
    const arr3 m_colour;
};

#endif
