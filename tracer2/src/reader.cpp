#include "reader.h"
#include "sphere.h"
#include "triangle.h"

using namespace std;
using namespace tinyobj;


namespace RT {

vec3 read_pos(const vector<float>& f, int idx) {
    return vec3(f[idx * 3], f[idx * 3 + 1], f[idx * 3 + 2]);
}

Triangle read_triangle(const vector<float>& f, const vector<uint>& indices,
                       int idx) {
    return Triangle(read_pos(f, indices[idx * 3]),
                    read_pos(f, indices[idx * 3 + 1]),
                    read_pos(f, indices[idx * 3 + 2]));
}

geo_ptr toBHV(const shape_t& shape) {
    vector<Triangle> triangles;
    vector<int> indices;
    auto& mesh = shape.mesh;
    for (size_t i = 0; i < mesh.indices.size() / 3; i++) {
        triangles.push_back(read_triangle(mesh.positions, mesh.indices, i));
        indices.push_back(i);
    }
    geo_ptr ptr;
    ptr.reset(new BHV<Triangle>(triangles, indices));
    return ptr;
}
bool read_meshes(const string filename, vector<geo_ptr>& geos) {
    vector<shape_t> _shapes;
    vector<material_t> _materials;
    string err;
    bool ret = LoadObj(_shapes, _materials, err, filename.c_str());
    if (!err.empty()) cerr << err << endl;
    if (!ret) return false;
    for (auto& shape : _shapes) {
        geos.push_back(toBHV(shape));
    }
    return true;
}
}
