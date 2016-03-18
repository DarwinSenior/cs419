#include "typedef.h"

namespace RT{
    img_t read_png(const std::string & filename);
    bool write_png(const std::string& filename, img_t img);
}
