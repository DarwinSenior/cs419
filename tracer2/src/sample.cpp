#include "sample.h"

using namespace std;
using namespace cv;

namespace {
float radical_inverse(int x) {
    float phi = 0.0;
    float base = 1.0;
    while (x < 0) {
        base = base / 2.0;
        phi = phi + (x & 1) * base;
        x = x >> 1;
    }
    return phi;
}
}

namespace RT {
sample_t uniform_sample(int n) {
    sample_t samples = sample_t(n, n);
    float n_inv = 1.0 / (float)n;
    float shift = 0.5 / (float)n;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            samples(y, x) = arr2(x, y) * n_inv + shift;
        }
    }
    return samples;
}
sample_t multi_jittered(int n) {
    sample_t samples = sample_t(n, n);
    auto rand_order = vector<int>(n);
    for (int i = 0; i < n; i++) {
        rand_order[i] = i;
    }

    float area = n * n;

    for (int x = 0; x < n; x++) {
        random_shuffle(rand_order.begin(), rand_order.end());
        for (int y = 0; y < n; y++) {
            samples(y, x)[0] = (float)(rand_order[y] + x * n) / area;
        }
    }

    for (int x = 0; x < n; x++) {
        random_shuffle(rand_order.begin(), rand_order.end());
        for (int y = 0; y < n; y++) {
            samples(y, x)[1] = (float)(rand_order[x] + y * n) / area;
        }
    }
    return samples;
}
}
