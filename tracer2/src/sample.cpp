#include "sample.h"

using namespace std;
using namespace cv;

namespace{
    float radical_inverse(int x){
        float phi = 0.0;
        float base = 1.0;
        while (x<0){
            base = base/2.0;
            phi = phi + (x & 1)*base;
            x = x>>1;
        }
        return phi;
    }

}

namespace RT{
    Mat2f uniform_sample(int n){
        Mat2f samples = Mat2f(n, n);
        float shift = 0.5/(float)n;
        for (int y=0; y<n; y++){
            for (int x=0; x<n; x++){
                samples[y][x][0] = (float)x/(float)n + shift;
                samples[y][x][1] = (float)y/(float)n + shift;
            }
        }
        return samples;
    }
    Mat2f multi_jittered(int n){
        Mat2f samples = Mat2f(n, n);
        auto rand_order = vector<int>(n);
        for (int i=0; i<n; i++){
            rand_order[i] = i;
        }
        for (int x=0; x<n; x++){
            random_shuffle(rand_order.begin(), rand_order.end());
            for (int y=0; y<n; y++){
                samples[y][x][0] = (float)(rand_order[y]+x*n)/(float)(n*n);
            }
        }
        for (int x=0; x<n; x++){
            random_shuffle(rand_order.begin(), rand_order.end());
            for (int y=0; y<n; y++){
                samples[y][x][1] = (float)(rand_order[x]+y*n)/(float)(n*n);
            }
        }
        return samples;
    }
}
