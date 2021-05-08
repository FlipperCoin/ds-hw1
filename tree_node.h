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
             SharedPointer<TreeNode<DataType>> big,
             DataType key) : Small(small), Big(big), Sons(2) {
        Indices[0] = key;
    }
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middle,
             SharedPointer<TreeNode<DataType>> big,
             DataType key1,
             DataType key2) : Small(small), MiddleOne(middle), Big(big), Sons(3) {
        Indices[0] = key1;
        Indices[1] = key2;
    }
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middleOne,
             SharedPointer<TreeNode<DataType>> middleTwo,
             SharedPointer<TreeNode<DataType>> big,
             DataType key1,
             DataType key2,
             DataType key3) : Small(small), MiddleOne(middleOne), MiddleTwo(middleTwo),
             Big(big), Sons(4) {
        Indices[0] = key1;
        Indices[1] = key2;
        Indices[2] = key3;
    }
    TreeNode(DataType value) : Value(value), Small(SharedPointer<TreeNode<DataType>>()), Sons(0) {
    }

    void insertValue(DataType value){
        for (int i = 0; i < sons; ++i) {

        }
    }
};


#endif //DS_EX1_TREE_NODE_H
