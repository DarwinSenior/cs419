#include "directional_light.h"
#include <cmath>

using namespace std;
using namespace cv;

DirLight::DirLight(Vec3f dir, float i){
    m_dir = normalize(dir);
    m_i = i;
}

float DirLight::intensity(const Intersect& inter){
    float kd = inter.material.kd;
    float ks = inter.material.ks;
    float alpha = inter.material.alpha;
    auto R = 2*inter.norm-m_dir;
    float i_d = kd*(inter.norm.dot(m_dir))*m_i;
    float i_s = ks*(pow(R.dot(inter.raydir), alpha))*m_i;
    return std::max<float>(i_d, 0.0)+std::max<float>(i_s, 0.0);
}



