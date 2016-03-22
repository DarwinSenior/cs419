#ifndef READER_H_
#define READER_H_

#include <memory>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "../lib/tiny_obj_loader.h"
#include "BHV.h"
#include "geometry.h"
#include "typedef.h"

#define TINYOBJLOADER_IMPLEMENTATION

namespace RT {
bool read_meshes(const std::string filename, std::vector<geo_ptr>& geo, float scalar=1.0);
}

#endif
