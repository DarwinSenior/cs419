#include "BHV.h"
#include <algorithm>
#include "sphere.h"
#include "triangle.h"

using namespace std;

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

using idx_t = vector<int>::iterator;
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
    const auto& begin = node->begin;
    const auto& end = node->end;
    const auto& middle = begin + (end - begin) / 2;
    nth_element(begin, middle, end, SplitCmp<T>(axis, geos));
}

template <class T>
BHVNode* create_node(const vector<T>& geos, idx_t begin, idx_t end) {
    BHVNode* node = new BHVNode();
    // node->indicies = vector<int>(begin, end);
    node->begin = begin;
    node->end = end;
    node->box = AABB(begin, end, geos);
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*
 *  testing intersection on leaf case, try intersect every node
 */
template <class T>
bool intersect_(const idx_t begin, const idx_t end, const vector<T>& geos,
                const Ray& ray, Intersect& inter) {
    bool intersected = false;
    for (auto it = begin; it < end; it++) {
        intersected = geos[*it].intersect(ray, inter) || intersected;
    }
    return intersected;
}

/**
 *  intersection on nodes recursively
 *  it used the referenced points for intersection
 */
template <class T>
bool intersect_(const BHVNode* node, const vector<T>& geos, const Ray& ray,
                Intersect& inter) {
    if (node->is_leaf()) {
        return intersect_(node->begin, node->end, geos, ray, inter);
    } else {
        float left_dist = node->left->box.intersect(ray);
        float right_dist = node->right->box.intersect(ray);
        BHVNode* first = node->left;
        BHVNode* second = node->right;
        bool intersected = false;
        if (left_dist > right_dist) {
            swap(first, second);
            swap(left_dist, right_dist);
        }
        if (left_dist < inter.dist) {
            intersected = intersect_(first, geos, ray, inter) || intersected;
        }
        if (right_dist < inter.dist) {
            intersected = intersect_(second, geos, ray, inter) || intersected;
        }
        return intersected;
    }
}
}

template <class T>
BHV<T>::BHV(vector<T> geos, vector<int> indicies)
    : m_geos(geos), m_indicies(indicies), m_root(NULL) {
    m_root = create_node(geos, m_indicies.begin(), m_indicies.end());
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
    return intersect_(m_root, m_geos, ray, inter);
}

template <class T>
void BHV<T>::build(BHVNode* node, size_t depth) {
    int axis = depth % 3;
    int size = node->end - node->begin;
    if (depth < MAX_DEPTH && size > MIN_ITEMS) {
        split_node(node, axis, m_geos);
        const auto& begin = node->begin;
        const auto& end = node->end;
        const auto& middle = begin + (end - begin) / 2;
        node->left = create_node(m_geos, begin, middle);
        node->right = create_node(m_geos, middle, end);
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
    cout << prefix << "(" << node->box.volume() << ','
         << node->end - node->begin << ")" << endl;

    if (node->left && prefix.length() < 5) print(node->left, prefix + "L");

    if (node->right && prefix.length() < 5) print(node->right, prefix + "R");
}
