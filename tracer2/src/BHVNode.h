#ifndef BHVNODE_H_
#define BHVNODE_H_

#include <iostream>
#include "typedef.h"
#include <vector>

#include "AABB.h"

struct BHVNode {
    AABB box;

    BHVNode* left;
    BHVNode* right;
    std::vector<int>::iterator begin;
    std::vector<int>::iterator end;

    ~BHVNode() {
        delete left;
        delete right;
    }
    bool is_leaf() const { return (left == NULL) && (right == NULL); }
};

#endif
