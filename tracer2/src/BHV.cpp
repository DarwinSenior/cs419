#include "BHV.h"
#include <algorithm>
#include "sphere.h"
#include "triangle.h"

using namespace std;
using namespace cv;

void BHV_CODE_GENERATOR() {
    vector<Triangle> tris;
    vector<Sphere> sphs;
    vector<int> idxs;
    BHV<Triangle> a(tris, idxs);
    BHV<Sphere> b(sphs, idxs);
    BHV<Triangle> c(tris);
    BHV<Sphere> d(sphs);
    c = a;
    Ray ray;
    Intersect inter(ray);
    a.intersect(ray, inter);
    b.intersect(ray, inter);
    a.print();
    b.print();
    a = c;
    b = d;
}

namespace {

const float INF = std::numeric_limits<float>::infinity();

int number_of_intersection = 0;

vector<int> sequence(int size) {
    vector<int> indices(size);
    for (size_t i = 0; i < indices.size(); i++) {
        indices[i] = i;
    }
    return indices;
}

// functions below are for creating the hirachical structure
template <class T>
class SplitCmp {
   public:
    SplitCmp(int axis, const vector<T>& geos) : m_axis(axis), m_geos(geos) {}

    bool operator()(const int& i1, const int& i2) {
        auto& t1 = m_geos[i1];
        auto& t2 = m_geos[i2];
        float n1 = t1.center()[m_axis];
        float n2 = t2.center()[m_axis];
        return n1 < n2;
    }

   private:
    int m_axis;
    const vector<T>& m_geos;
};

template <class T>
void split_node(BHVNode* node, int axis, const vector<T>& geos) {
    auto& indicies = node->indicies;
    nth_element(indicies.begin(), indicies.begin() + indicies.size() / 2,
                indicies.end(), SplitCmp<T>(axis, geos));
}

template <class T>
BHVNode* create_node(const vector<T>& geos, vector<int>::iterator begin,
                     vector<int>::iterator end) {
    BHVNode* node = new BHVNode();
    node->indicies = vector<int>(begin, end);
    node->box = AABB(node->indicies, geos);
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*
 *  testing intersection on leaf case, try intersect every node
 */
template <class T>
void intersect_(const vector<int> indicies, const vector<T>& geos,
                const Ray& ray, Intersect& inter) {
    for (auto& idx : indicies) {
        geos[idx].intersect(ray, inter);
    }
}

/**
 *  intersection on nodes recursively
 *  it used the referenced points for intersection
 */
template <class T>
void intersect_(const BHVNode* node, const vector<T>& geos, const Ray& ray,
                Intersect& inter) {
    if (node->is_leaf()) {
        intersect_(node->indicies, geos, ray, inter);
    } else {
        float left_dist = node->left->box.intersect(ray);
        float right_dist = node->right->box.intersect(ray);
        BHVNode* first = node->left;
        BHVNode* second = node->right;
        if (left_dist > right_dist) {
            swap(first, second);
            swap(left_dist, right_dist);
        }
        if (left_dist < inter.dist) {
            intersect_(first, geos, ray, inter);
        }
        if (right_dist < inter.dist) {
            intersect_(second, geos, ray, inter);
        }
    }
}
}

template <class T>
BHV<T>::BHV(vector<T> geos, vector<int> indicies)
    : m_geos(geos), m_indicies(indicies), m_root(NULL) {
    m_root = create_node(geos, indicies.begin(), indicies.end());
    build(m_root, 0);
}

template <class T>
BHV<T>::BHV(vector<T> geos) : BHV<T>(geos, sequence(geos.size())) {}

template <class T>
BHV<T>::~BHV() {
    clear();
}

template <class T>
bool BHV<T>::intersect(const Ray& ray, Intersect& inter) const {
    float dist = m_root->box.intersect(ray);

    if (dist < inter.dist) {
        intersect_(m_root, m_geos, ray, inter);
        return true;
    } else {
        return false;
    }
}

template <class T>
void BHV<T>::build(BHVNode* node, size_t depth) {
    int axis = depth % 3;
    if (depth < MAX_DEPTH && node->indicies.size() > MIN_ITEMS) {
        split_node(node, axis, m_geos);
        auto& idxs = node->indicies;
        auto middle = idxs.begin() + idxs.size() / 2;
        node->left = create_node(m_geos, idxs.begin(), middle);
        node->right = create_node(m_geos, middle, idxs.end());
        build(node->left, depth + 1);
        build(node->right, depth + 1);
    }
}

template <class T>
void BHV<T>::clear() {
    if (m_root) {
        delete m_root;
        m_root = NULL;
    }
}

template <class T>
void BHV<T>::print() {
    print(m_root, "O");
}

template <class T>
void BHV<T>::print(BHVNode* node, const string& prefix) {
    cout << prefix << "(" << node->box.volume() << ',' << node->indicies.size()
         << ")" << endl;

    if (node->left && prefix.length() < 5) print(node->left, prefix + "L");

    if (node->right && prefix.length() < 5) print(node->right, prefix + "R");
}
