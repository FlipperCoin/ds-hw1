//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_TREE_NODE_H
#define DS_EX1_TREE_NODE_H

template <typename DataType>
struct TreeNode {
    Vector<int> Indices;

    DataType Value;

    SharedPointer<TreeNode> Left;
    SharedPointer<TreeNode> Middle;
    SharedPointer<TreeNode> Right;
    SharedPointer<TreeNode> Extra;
};


#endif //DS_EX1_TREE_NODE_H
