#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "geometry.h"

struct Object{
    const Material& material;
    const Geometry& geometry;


    Object(Material& mat, Geometry& geo):
        material(mat), geometry(geo){}

    void updateIntersection(const Ray& ray, Intersect& inter){
        auto new_inter = Intersect();
        geometry.intersect(ray, new_inter);
        if (new_inter.dist < inter.dist){
            inter.pos = new_inter.pos;
            inter.dist = new_inter.dist;
            inter.norm = new_inter.norm;
            inter.material = material;
        }
    }
};


#endif
