#include "reader.h"
#include "sphere.h"
#include "triangle.h"

using namespace std;
using namespace cv;
using namespace tinyobj;


namespace RT {

Vec3f read_pos(const vector<float>& f, int idx) {
    return Vec3f(f[idx * 3], f[idx * 3 + 1], f[idx * 3 + 2]);
}

Triangle read_triangle(const vector<float>& f, const vector<uint>& indices,
                       int idx, float scalar) {
    return Triangle(read_pos(f, indices[idx * 3]*scalar),
                    read_pos(f, indices[idx * 3 + 1]*scalar),
                    read_pos(f, indices[idx * 3 + 2]*scalar));
}

geo_ptr toBHV(const shape_t& shape, float scalar) {
    vector<Triangle> triangles;
    vector<int> indices;
    auto& mesh = shape.mesh;
    for (size_t i = 0; i < mesh.indices.size() / 3; i++) {
        triangles.push_back(read_triangle(mesh.positions, mesh.indices, i, scalar));
        indices.push_back(i);
    }
    geo_ptr ptr;
    ptr.reset(new BHV<Triangle>(triangles, indices));
    return ptr;
}
bool read_meshes(const string filename, vector<geo_ptr>& geos, float scalar) {
    vector<shape_t> _shapes;
    vector<material_t> _materials;
    string err;
    bool ret = LoadObj(_shapes, _materials, err, filename.c_str());
    if (!err.empty()) cerr << err << endl;
    if (!ret) return false;
    for (auto& shape : _shapes) {
        geos.push_back(toBHV(shape, scalar));
    }
    return true;
}
}
