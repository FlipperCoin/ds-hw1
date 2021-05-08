//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_TREE_NODE_H
#define DS_EX1_TREE_NODE_H

#include "vector.h"
#include "shared_pointer.h"

template <typename DataType>
struct TreeNode {
    Vector<DataType> Indices=Vector<DataType>(3);
    int Sons;

    DataType Value;

    SharedPointer<TreeNode> Small;
    SharedPointer<TreeNode> MiddleOne;
    SharedPointer<TreeNode> MiddleTwo;
    SharedPointer<TreeNode> Big;


    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> big) : Small(small), Big(big), Sons(2) {
        Indices[0] = big;
    }
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middle,
             SharedPointer<TreeNode<DataType>> big) : Small(small), MiddleOne(middle), Big(big), Sons(3) {
        Indices[0] = middle;
        Indices[1] = big
    }
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middleOne,
             SharedPointer<TreeNode<DataType>> middleTwo,
             SharedPointer<TreeNode<DataType>> big) : Small(small), MiddleOne(middleOne), MiddleTwo(middleTwo),
             Big(big), Sons(4) {
        Indices[0] = middleOne;
        Indices[1] = middleTwo;
        Indices[2] = Big;
    }
    TreeNode(DataType value) : Value(value), Sons(0) {
        Small = SharedPointer<TreeNode<DataType>>();
    }
};


#endif //DS_EX1_TREE_NODE_H
