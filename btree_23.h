//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_TREE23_H
#define DS_EX1_TREE23_H

#include "tree_node.h"
#include "shared_pointer.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template <typename DataType>
class BTree23 {
private:
    SharedPointer<TreeNode<DataType>> root;
public:
    BTree23() = default;
    explicit BTree23(SharedPointer<TreeNode<DataType>> root = SharedPointer<TreeNode<DataType>>());
    void insert(DataType value);
    SharedPointer<TreeNode<DataType>> remove(DataType value);
    SharedPointer<TreeNode<DataType>> find(DataType value,
                                           SharedPointer<TreeNode<DataType>> node = SharedPointer<TreeNode<DataType>>());
    void inOrder(void (*action)(DataType), int limit = -1);
    void printTree(SharedPointer<TreeNode<DataType>> node = SharedPointer<TreeNode<DataType>>(), bool is_right_most = true, const string& prefix = "") const;
    bool isLeaf(SharedPointer<TreeNode<DataType>> node);
    void printMidNode(const SharedPointer<TreeNode<DataType>> &node) const;
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
        return find(value, node->Small);
    }

    if (node->Indices.getCount() == 1) return find(value, node->MiddleOne);

    //if (value >=)
}

template<typename DataType>
void BTree23<DataType>::inOrder(void (*action)(DataType), int limit) {

}

template<typename DataType>
void BTree23<DataType>::printTree(SharedPointer<TreeNode<DataType>> node, bool is_right_most, const string& prefix) const {
    if (isLeaf(node)) {
        cout << node->Value.str() << endl;
        return;
    }

    if (!is_right_most) cout << prefix;
    printMidNode(node);
    cout << "-";
    if (!node->Big.isEmpty()) {
        printTree(node->Big, true, prefix + "| ");
        cout << prefix << "|-";
    }
    printTree(node->MiddleOne, node->Big.isEmpty(), prefix + "| ");
    cout << prefix << "\\-";
    printTree(node->Small, false, prefix + "  ");
}

template<typename DataType>
void BTree23<DataType>::printMidNode(const SharedPointer<TreeNode<DataType>> &node) const {
    cout << "[";
    for (int i = 0; i < node->Indices.GetCount(); i++) {
        cout << node->Indices[i].str();
        if (i != node->Indices.GetCount()) {
            cout << ",";
        }
    }
    cout << "]";
}

template<typename DataType>
bool BTree23<DataType>::isLeaf(SharedPointer<TreeNode<DataType>> node) {
    return node->Left.isEmpty();
}

template<typename DataType>
BTree23<DataType>::BTree23(SharedPointer<TreeNode<DataType>> root) : root(root) { }


#endif //DS_EX1_TREE23_H
