#include "img_util.h"
#include "../lib/lodepng.h"

using namespace std;

namespace RT {
bool write_png(const std::string& filename, img_t img) {
    unsigned int height = img.rows();
    unsigned int width = img.cols();
    unsigned char image[height * width * 4];
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < height; x++) {
            for (int s = 0; s < 3; s++) {
                float value = max(255.f, min(0.f, img(y, x)[s] * 255));
                image[(y * width + x) * 4 + s] = (uchar)value;
            }
            image[(y * width + x) * 4 + 3] = 255;
        }
    }
    auto error = lodepng_encode32_file(filename.c_str(), image, width, height);
    if (error) {
        cerr << "error: " << lodepng_error_text(error) << endl;
        return false;
    } else {
        return true;
    }
}
}
