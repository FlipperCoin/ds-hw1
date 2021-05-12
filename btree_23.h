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
    explicit BTree23(SharedPointer<TreeNode<DataType>> root = SharedPointer<TreeNode<DataType>>());
    SharedPointer<TreeNode<DataType>> insert(DataType value);
    SharedPointer<TreeNode<DataType>> remove(DataType value);
    SharedPointer<TreeNode<DataType>> find(DataType value,
                                           SharedPointer<TreeNode<DataType>> node = SharedPointer<TreeNode<DataType>>()) const;
    void printTree() const;
    void printTree(SharedPointer<TreeNode<DataType>> node, bool is_right_most = true, const string& prefix = "") const;
    bool isLeaf(SharedPointer<TreeNode<DataType>> node) const;
    void printMidNode(const SharedPointer<TreeNode<DataType>> &node) const;
    void fix(SharedPointer<TreeNode<DataType>> node);
    bool operator==(const BTree23<DataType>& other) const;
    static bool compare(const TreeNode<DataType>& node1, const TreeNode<DataType>& node2);
};

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::insert(DataType value) {
    if (root.isEmpty()) {
        root = SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(value)); // add new tree node
        return root;
    }

    if (isLeaf(root)) {
        SharedPointer<TreeNode<DataType>> new_root =
                SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(DataType()));
        SharedPointer<TreeNode<DataType>> new_node =
                SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(value, new_root));
        root->Parent = new_root;
        new_root->Sons = 2;
        if(value < root->Value){
            new_root->Children[0] = new_node;
            new_root->Children[1] = root;
            new_root->Indices[0] = root->Value;
        }
        else {
            new_root->Children[0] = root;
            new_root->Children[1] = new_node;
            new_root->Indices[0] = new_node->Value;
        }
        root = new_root;
    }

    SharedPointer<TreeNode<DataType>> place = find(value, root);
    if (isLeaf(place)) { // value is already in tree!
        return SharedPointer<TreeNode<DataType>>();
    }
    // else - insert new node in father
    SharedPointer<TreeNode<DataType>> new_node =
            SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(value, place));
    place->insertValue(new_node);
    if(place->Sons == 3) return new_node; //great! no need for fixing!
    fix(place);
    return new_node;
}

template<typename DataType>
void BTree23<DataType>::fix(SharedPointer<TreeNode<DataType>> node) {
    auto first_half = SharedPointer<TreeNode<DataType>>(
            new TreeNode<DataType>(node->Children[0], node->Children[1], node->Indices[0]));
    auto second_half = SharedPointer<TreeNode<DataType>>(
            new TreeNode<DataType>(node->Children[2], node->Children[3], node->Indices[2]));
    if (node->Parent.isEmpty()){
        root = SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(first_half, second_half,node->Indices[1]));
        return;
    }
    node->Parent->swap(first_half, second_half,node->Indices[1]);
    if (node->Parent->Sons == 4)
        fix(node->Parent);
}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::remove(DataType value) {
    SharedPointer<TreeNode<DataType>> node = find(value, root);
    if(!isLeaf(node)){ // check if the value doesn't exist
        return SharedPointer<TreeNode<DataType>>(); // what to give back ????
    }
    if (node->Parent == SharedPointer<TreeNode<DataType>>()){
        root = SharedPointer<TreeNode<DataType>>();
        return root;
    }
    SharedPointer<TreeNode<DataType>> parent = node->Parent;
    parent.removeSon(value);
    if(parent == root && parent->Sons == 1){
        root == parent->Children[0];
        root->parent = SharedPointer<TreeNode<DataType>>();
        return root;
    }
    if (parent->Sons == 2) return parent;

    if (parent->Sons == 1){
        if (parent->Parent->Children[0]->Value == parent->Value) { // if this is the first child
            int direction = 1; // make change with right hand side
        }
        if (parent->Parent->Children[1]->Value == parent->Value) { // if this is the second child
            int direction = 0; // make change with left hand side

        if(parent->Parent->Sons == 3){
            if ((parent->Parent->Children[2]->Value == parent->Value) { // if this is the third child
                int direction = 0; // make change with left hand side
            }
            if (parent->Parent->Children[1]->Value == parent->Value && parent->Parent->Children[2]->Sons == 3) {
                direction = 1; // make change with left hand side
            }
        }



        if (parent->Parent->Children[1]->Value == parent->Value) {
            if (parent->Parent->Children[2]->Sons == 3) parent.borrow(1); // right
            else if (parent->Parent->Children[0]->Sons == 3) parent.borrow(0); // left
            else parent.combine(1);
        }

        if(parent->Parent->Children[1]->Sons == 3){
            parent.borrow(direction);
        }
        else{
            parent.combine(direction);
        }


    }
    /*
    if (node->Parent->Sons == 3){
        node.removeThirdSon();
    }

    /*
    else if (node->Parent->Sons == 1){ // are there any other cases there's only one child?
        root = SharedPointer<TreeNode<DataType>>();
        return SharedPointer<TreeNode<DataType>>();
    }

     NOT SUPPOSED TO HAPPEN!!


    else if(node->Parent->Sons == 2){
        SharedPointer<TreeNode<DataType>> other_son = SharedPointer<TreeNode<DataType>>();
        if(node->parent->Children[0]->Value == value){
            other_son = node->parent->Children[1];
        }
        else{
            other_son = node->parent->Children[0];
        }

        if(node->parent == root){ // if parent is root then the other child will be the new root.
            if(root->Children[0] == node) {
                root = root->Children[1];
            }
            else {
                root= root->Children[0];
            }
        }

        else {
            if(node->Parent->Parent->Sons == 3) {
                if (node->Parent->Parent->Children[2] == node->Parent) {
                    if (node->Parent->Parent->Children[1].Sons == 2){
                        node->Parent->Parent->Children[1].Sons = 3;
                        node->Parent->Parent->Children[1].Indices[1] = other_son->Value;
                        node->Parent->Parent->Children[1].Children[2] = other_son;
                    }
                    else{
                        borrow_leaf(node->Parent->Parent->Children[1],2)
                    }
                }
            }

        }
    }

    // node->Parent->Sons--; done in remove third son

     */

    return SharedPointer<TreeNode<DataType>>();

}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::find(DataType value, SharedPointer<TreeNode<DataType>> node) const {
    // first run, init from root
    if (node.isEmpty()) {
        node = root;
    }

    // reached a leaf, its either the wanted value or the value is not in the tree
    if (isLeaf(node)) {
        // return an empty pointer indicating the value's not in the tree
        // and the parent should be returned instead
        if (!(value == node->Value)) {
            return SharedPointer<TreeNode<DataType>>();
        }

        // return the found leaf with the wanted value
        return node;
    }

    SharedPointer<TreeNode<DataType>> found;
    for (int i = 0; i < node->Sons-1; i++) {
        // if not less than this part, check if it was the last part
        if (!(value < node->Indices[i])) {
            if (i == node->Sons-2) {
                // definitely larger equals node->Indices[node->Sons-1])
                found = find(value, node->Children[i+1]);
            }

            // if not the last, continue in the loop
            continue;
        };

        // value is in this part, try find and break
        found = find(value, node->Children[i]);
        break;
    }

    // if didn't find, return parent
    if (found.isEmpty()) {
        return node;
    }

    // return leaf (or parent from below)
    return found;
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
    return compare(*root, *(other.root));
}

template<typename DataType>
bool BTree23<DataType>::compare(const TreeNode<DataType> &node1, const TreeNode<DataType> &node2) {
    if (node1.Sons != node2.Sons) return false;

    for (int i = 0; i < node1.Sons-1; i++) {
        if (node1.Indices[i] != node2.Indices[i]) {
            return false;
        }
    }

    for (int i = 0; i < node1.Sons; i++) {
        if (!compare(*(node1.Children[i]),*(node2.Children[i]))) {
            return false;
        }
    }

    return true;
}

#endif //DS_EX1_TREE23_H
