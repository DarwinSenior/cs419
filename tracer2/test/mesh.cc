#include "catch.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "../lib/tiny_obj_loader.h"

#include "../src/AABB.h"
#include "../src/BHV.h"
#include "../src/triangle.h"
#include "../src/typedef.h"

using namespace tinyobj;
using namespace std;

namespace {

vec3 read_pos(const vector<float>& f, int idx) {
    return vec3(f[idx * 3], f[idx * 3 + 1], f[idx * 3 + 2]);
}

Triangle read_triangle(const vector<float>& f, const vector<uint>& indices,
                       int idx) {
    return Triangle(read_pos(f, indices[idx * 3]),
                    read_pos(f, indices[idx * 3 + 1]),
                    read_pos(f, indices[idx * 3 + 2]));
}

float randp() { return rand() / float(RAND_MAX); }

Sphere generate_spheres(float r, const AABB& size) {
    return Sphere(randp() * (size.max_p() - size.min_p()) + size.min_p(), r);
}

template <class T>
Ray random_ray(const vector<T>& ts) {
    Ray ray;
    AABB box(ts);
    int idx = rand() % ts.size();
    ray.o = vec3(0, 0, 0);
    ray.d = (ts[idx].center() - ray.o).normalized();
    Intersect inter(ray);
    ts[idx].intersect(ray, inter);
    return ray;
}

template <class T>
float bruteforce_tracer(const vector<T>& ts, const Ray& ray) {
    Intersect inter(ray);
    for (auto& tri : ts) {
        tri.intersect(ray, inter);
    }
    return inter.dist;
}

template <class T>
float bounder_tracer(const BHV<T>& bounder, const Ray& ray) {
    Intersect inter(ray);
    inter.noIntersection();
    bounder.intersect(ray, inter);
    return inter.dist;
}
}

TEST_CASE("testing reading obj file", "[mesh]") {
    vector<shape_t> shapes;
    vector<material_t> materials;
    string inputfile = "cow.obj";
    string err;
    bool ifreturned = LoadObj(shapes, materials, err, inputfile.c_str());
    REQUIRE(err.empty());
    REQUIRE(ifreturned);
    REQUIRE(shapes.size() == 1);

    auto& cow = shapes[0];
    INFO("number of verticies" << cow.mesh.indices.size());
    INFO("number of normals" << cow.mesh.normals.size());
}

TEST_CASE("TESTING with simple splitting", "[mesh]") {
    vector<shape_t> shapes;
    vector<material_t> materials;
    string inputfile = "box.obj";
    string err;
    bool ifreturned = LoadObj(shapes, materials, err, inputfile.c_str());
    auto& cow = shapes[0];
    vector<Triangle> triangles;
    for (size_t i = 0; i < cow.mesh.indices.size() / 3; i++) {
        triangles.push_back(
            read_triangle(cow.mesh.positions, cow.mesh.indices, i));
    }
    BHV<Triangle> bounder(triangles);
    for (int i = 0; i < 200; i++) {
        auto ray = random_ray(triangles);
        REQUIRE(bruteforce_tracer(triangles, ray) ==
                (bounder_tracer(bounder, ray)));
    }
}

TEST_CASE("TESTING with triangle splitting", "[mesh]") {
    vector<shape_t> shapes;
    vector<material_t> materials;
    string inputfile = "bunny.obj";
    string err;
    bool ifreturned = LoadObj(shapes, materials, err, inputfile.c_str());
    auto& cow = shapes[0];
    vector<Triangle> triangles;
    for (size_t i = 0; i < cow.mesh.indices.size() / 3; i++) {
        triangles.push_back(
            read_triangle(cow.mesh.positions, cow.mesh.indices, i));
    }
    BHV<Triangle> bounder(triangles);
    for (int i = 0; i < 200; i++) {
        auto ray = random_ray(triangles);
        REQUIRE(bruteforce_tracer(triangles, ray) ==
                (bounder_tracer(bounder, ray)));
    }
}

TEST_CASE("TESTING with sphere splitting", "[mesh]") {
    vector<Sphere> spheres;
    vec3 bound(100, 100, 100);
    for (size_t i = 0; i < 7000; i++) {
        spheres.push_back(generate_spheres(0.1, AABB(-bound, bound)));
    }
    BHV<Sphere> bounder(spheres);
    for (int i = 0; i < 200; i++) {
        auto ray = random_ray(spheres);
        REQUIRE(bruteforce_tracer(spheres, ray) ==
                (bounder_tracer(bounder, ray)));
    }
}
