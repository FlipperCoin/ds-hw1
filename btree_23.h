#ifndef DS_EX1_TREE23_H
#define DS_EX1_TREE23_H

#include "tree_node.h"
#include "shared_pointer.h"

#include <iostream>
#include <string>
#include "vector.h"

using std::cout;
using std::endl;
using std::string;

template <typename DataType>
class BTree23 {
private:
    SharedPointer<TreeNode<DataType>> root;
public:
    explicit BTree23(SharedPointer<TreeNode<DataType>> root = SharedPointer<TreeNode<DataType>>());
    // tree with ascending values from 0 to n-1
    explicit BTree23(int n);
    SharedPointer<TreeNode<DataType>> insert(DataType value);
    SharedPointer<TreeNode<DataType>> remove(DataType value);
    SharedPointer<TreeNode<DataType>> find(DataType value,
                                           SharedPointer<TreeNode<DataType>> node = SharedPointer<TreeNode<DataType>>(),
                                           bool updateOnPath = false) const;
    void printTree() const;
    void printTree(SharedPointer<TreeNode<DataType>> node, bool is_right_most = true, const string& prefix = "") const;
    void run(void (*action)(SharedPointer<TreeNode<DataType>>),
                  void (*should_continue)(SharedPointer<TreeNode<DataType>>));
    bool isLeaf(SharedPointer<TreeNode<DataType>> node) const;
    void printMidNode(const SharedPointer<TreeNode<DataType>> &node) const;
    void fix_insert(SharedPointer<TreeNode<DataType>> node);
    void fix_remove(SharedPointer<TreeNode<DataType>> node);
    bool operator==(const BTree23<DataType>& other) const;
    static bool compare(const TreeNode<DataType>& node1, const TreeNode<DataType>& node2);

    void createRow(Vector<SharedPointer<TreeNode<int>>> &nodes, int k, int r) const;

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
void BTree23<DataType>::fix_insert(SharedPointer<TreeNode<DataType>> node) {
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
        fix_insert(node->Parent);
}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::remove(DataType value) {
    SharedPointer<TreeNode<DataType>> node = find(value, root);
    if (!isLeaf(node)) { // check if the value doesn't exist
        return SharedPointer<TreeNode<DataType>>(); // what to give back ????
    }
    if (node->Parent == SharedPointer<TreeNode<DataType>>()) {
        root = SharedPointer<TreeNode<DataType>>();
        return root;
    }
    SharedPointer<TreeNode<DataType>> v_node = node->Parent;
    v_node.removeSon(value);

    // recursive function here!!
    fix_remove(v_node);
    return SharedPointer<TreeNode<DataType>>();
}

template<typename DataType>
void BTree23<DataType>::fix_remove(SharedPointer<TreeNode<DataType>> v_node) {
    if (v_node->Sons != 1) return;

    if (v_node == root) {
        root == v_node->Children[0];
        root->Parent = nullptr;
        return;
    }
    // v_node has one son but he's not root
    if (v_node->Parent->Children[0]->Value == v_node->Value) { // if this is first child - id = 0
        if (v_node->Parent->Children[1]->Sons == 3) v_node.borrow(0, 1); // borrow from second child
        else v_node.combine(0, 1); // combine with second child
    }
    else if (v_node->Parent->Children[1]->Value == v_node->Value) { // if this is middle child - id = 1
        if (v_node->Parent->Children[0]->Sons == 3) v_node.borrow(1, 0); // borrow from first child
        else if (v_node->Parent->Sons == 3) { // if parent has three sons
            if (v_node->Parent->Children[2]->Sons == 3) v_node.borrow(1, 2); // borrow from third side
            else v_node.combine(1, 2); // combine with third side

        }
        else v_node.combine(1, 0);
    }
    else { // this is the third child - id = 2
        if (v_node->Parent->Children[1]->Sons == 3) v_node.borrow(2, 1);
        else v_node.combine(2, 1);
    }
    fix_remove(v_node->Parent);
}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::find(DataType value,
                                                          SharedPointer<TreeNode<DataType>> node,
                                                          bool updateOnPath) const {
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

    // if find should update on path the smallest value in the node's subtrees
    if (updateOnPath && (node->Value > value)) {
        node->Value = value;
    }

    // recall find on correct subtree
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
    if (root.isEmpty()) {
        return other.root.isEmpty();
    }
    else if (other.root.isEmpty()) {
        return false;
    }

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

template<>
BTree23<int>::BTree23(int n) {
    if (n == 0) {
        root = SharedPointer<TreeNode<int>>();
        return;
    }

    // create references for all nodes in final tree,
    // less than 2*n for n leaves
    Vector<SharedPointer<TreeNode<int>>> nodes(2*n);

    // create row of leaves
    for (int i = 0; i < n; i++) {
        nodes.add(SharedPointer<TreeNode<int>>(new TreeNode<int>(i)));
    }

    // loop row by row, from the bottom up
    // each time creating the row's parents and linking them
    int k = n;
    int r = 0;
    while (r+k - r > 1) {
        createRow(nodes, k, r);
        r += k;
        k /= 2; // rounding down is a wanted behaviour, in case of 3 sons in the end
    }

    root = nodes[r];
}

template<typename DataType>
void BTree23<DataType>::createRow(Vector<SharedPointer<TreeNode<int>>> &nodes, int k, int r) const {
    for (int i = r; i < r + k; i+=2) {
        SharedPointer<TreeNode<int>> parent;

        // if only 3 left, add a parent to 3 sons
        if ((r+k - i) == 3) {
            parent = SharedPointer<TreeNode<int>>(
                    new TreeNode<int>(
                            nodes[i],
                            nodes[i+1],
                            nodes[i+2],
                            nodes[i+1]->Value,
                            nodes[i+2]->Value
                    ));
            // use the Value field in non-leaves to save the lowest value under it
            parent->Value = nodes[i]->Value;
            nodes.add(parent);
            nodes[i]->Parent = parent;
            nodes[i+1]->Parent = parent;
            nodes[i+2]->Parent = parent;
            break;
        }
            // add a parent with 2 sons
        else {
            parent = SharedPointer<TreeNode<int>>(
                    new TreeNode<int>(
                            nodes[i],
                            nodes[i+1],
                            nodes[i+1]->Value
                    ));
            parent->Value = nodes[i]->Value;
        }

        nodes.add(parent);
        nodes[i]->Parent = parent;
        nodes[i+1]->Parent = parent;
    }
}

template<typename DataType>
void BTree23<DataType>::run(void (*action)(SharedPointer<TreeNode<DataType>>),
                            void (*should_continue)(SharedPointer<TreeNode<DataType>>)) {

}

#endif //DS_EX1_TREE23_H
