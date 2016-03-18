#ifndef SAMPLE_H
#define SAMPLE_H

#include <vector>
#include "typedef.h"
namespace RT{
    sample_t uniform_sample(int n);
    sample_t multi_jittered(int n);
    sample_t hammersley(int n);
}

#endif
