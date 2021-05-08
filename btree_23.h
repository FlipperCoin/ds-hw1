//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_TREE23_H
#define DS_EX1_TREE23_H

#include "tree_node.h"
#include "shared_pointer.h"

#include <iostream>

using std::cout;
using std::endl;

template <typename DataType>
class BTree23 {
private:
    SharedPointer<TreeNode<DataType>> root;
public:
    void insert(DataType value);
    SharedPointer<TreeNode<DataType>> remove(DataType value);
    SharedPointer<TreeNode<DataType>> find(DataType value,
                                           SharedPointer<TreeNode<DataType>> node = SharedPointer<TreeNode<DataType>>());
    void inOrder(void (*action)(DataType), int limit = -1);
    void printTree(SharedPointer<TreeNode<DataType>> node = nullptr);
};

template<typename DataType>
void BTree23<DataType>::insert(DataType value) {

}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::remove(DataType value) {
    return SharedPointer<TreeNode<DataType>>();
}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::find(DataType value, SharedPointer<TreeNode<DataType>> node) {
    if (node.isEmpty()) node = root;

    if (node->Indices.getCount() == 0) {
        if (!value == node->Value) return SharedPointer<TreeNode<DataType>>();

        return node;
    }

    if (value < node->Indices[0]) {
        return find(value, node->Left);
    }

    if (node->Indices.getCount() == 1) return find(value, node->Middle);

    if (value >=)
}

template<typename DataType>
void BTree23<DataType>::inOrder(void (*action)(DataType), int limit) {

}

template<typename DataType>
void BTree23<DataType>::printTree(SharedPointer<TreeNode<DataType>> node) {

}


#endif //DS_EX1_TREE23_H
