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
    SharedPointer<TreeNode<DataType>> insert(DataType value);
    SharedPointer<TreeNode<DataType>> remove(DataType value);
    SharedPointer<TreeNode<DataType>> find(DataType value,
                                           SharedPointer<TreeNode<DataType>> node = SharedPointer<TreeNode<DataType>>());
    void printTree() const;
    void printTree(SharedPointer<TreeNode<DataType>> node, bool is_right_most = true, const string& prefix = "") const;
    bool isLeaf(SharedPointer<TreeNode<DataType>> node) const;
    void printMidNode(const SharedPointer<TreeNode<DataType>> &node) const;
    void fix(SharedPointer<TreeNode<DataType>> node);
    bool operator==(const BTree23<DataType>& other) const;
    static bool compare(const TreeNode<DataType>& node1, const TreeNode<DataType>& node2);
};

template<typename DataType>
void BTree23<DataType>::insert(DataType value) {
    if (!root) {
        root = SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(value)); // add new tree node
        return;
    }
    SharedPointer<TreeNode<DataType>> place = find(value, root); // return the
    if (place.isleaf()) return; // value is already in tree!
    // else - insert new node in father
    SharedPointer<TreeNode<DataType>> new_node = new TreeNode<DataType>(value, place);
    place.InsertNode(new_node);
    if(sons == 3) return; //great! no need for fixing!
    fix(place);
    return;
}
SharedPointer<TreeNode<DataType>> BTree23<DataType>::insert(DataType value) {

template<typename DataType>
void BTree23<DataType>::fix(SharedPointer<TreeNode<DataType>> node) {
    SharedPointer<TreeNode<DataType>> first_half = new TreeNode<DataType>(node->children[0], node->children[1], node->Indices[0]);
    SharedPointer<TreeNode<DataType>> second_half = new TreeNode<DataType>(node->children[2], node->children[3], node->Indices[2]);
    if (node->parent == nullptr){
        root = SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(first_half, second_half,node->Indices[1]));
    }
    else node->parent.swap(first_half, second_half,node->Indices[1]);
    if (node->parent->sons == 4)
        fix(parent);
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
void BTree23<DataType>::printTree() const {
    printTree(root);
}
template<typename DataType>
void BTree23<DataType>::printTree(SharedPointer<TreeNode<DataType>> node, bool is_right_most, const string& prefix) const {
    if (isLeaf(node)) {
        cout << node->Value.str() << endl;
        return;
    }

    printMidNode(node);
    cout << "-";
    string padding = "";
    for (int i = 0; i < ((node->Sons-1)*2); i++) padding += " ";
    printTree(node->Children[node->Sons-1], true, prefix + padding + "| ");
    for (int i = node->Sons-2; i > 0; i--) {
        cout << prefix << padding << "|-";
        printTree(node->Children[i], false, prefix + padding + "| ");
    }
    cout << prefix << padding << "\\-";
    printTree(node->Children[0], false, prefix + padding + "  ");
}

template<typename DataType>
void BTree23<DataType>::printMidNode(const SharedPointer<TreeNode<DataType>> &node) const {
    cout << "[";
    for (int i = 0; i < node->Sons-1; i++) {
        cout << node->Indices[i].str();
        if (i != node->Sons-2) {
            cout << ",";
        }
    }
    cout << "]";
}

template<typename DataType>
bool BTree23<DataType>::isLeaf(SharedPointer<TreeNode<DataType>> node) const {
    return node->Sons == 0;
}

template<typename DataType>
BTree23<DataType>::BTree23(SharedPointer<TreeNode<DataType>> root) : root(root) { }

template<typename DataType>
bool BTree23<DataType>::operator==(const BTree23<DataType> &other) const {
    auto node = root;


}

template<typename DataType>
bool BTree23<DataType>::compare(const TreeNode<DataType> &node1, const TreeNode<DataType> &node2) {
    if (node1.Sons != node2.Sons) return false;

    for (int i = 0; i < node1.Sons; i++) {
        if (node1.Indices[i] != node2.Indices[i]) return false;
    }

    for (int i = 0; i < node1.Sons; i++) {
        if (!compare(node1.Children[i],node2.Children[i])) return false;
    }

    return true;
}

#endif //DS_EX1_TREE23_H
