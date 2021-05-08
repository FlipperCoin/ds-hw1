//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_TREE_NODE_H
#define DS_EX1_TREE_NODE_H

#include "vector.h"
#include "shared_pointer.h"

template <typename DataType>
struct TreeNode {
    Vector<DataType> Indices;

    DataType Value;

    SharedPointer<TreeNode> Left;
    SharedPointer<TreeNode> Middle;
    SharedPointer<TreeNode> Right;
    SharedPointer<TreeNode> Extra;
};


#endif //DS_EX1_TREE_NODE_H
