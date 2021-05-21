//
// Created by Itai on 08/05/2021.
//

#ifndef DS_EX1_TREE_NODE_H
#define DS_EX1_TREE_NODE_H

#include "vector.h"
#include "shared_pointer.h"

#include <iostream>

using std::cout;
using std::endl;

/**
 * Btree23 node
 * @tparam DataType the data type stored in the tree, used as the key type and the eventual value
 */
template <typename DataType>
struct TreeNode {
    /**
     * TreeNode keeps truck of its number of sons
     */
    int Sons;

    /**
     * Keys for routing in the tree, first is the smallest
     */
    Vector<DataType> Indices=Vector<DataType>(3);

    /**
     * Node's children, first is the smallest
     */
    Vector<SharedPointer<TreeNode<DataType>>> Children = Vector<SharedPointer<TreeNode<DataType>>>(4);

    /**
     * This field has to purposes, depending if this node is a leaf or not.
     * If its a leaf then this is it's value.
     * Otherwise, this is the value of the smallest leaf under this node (used for key transfers)
     */
    DataType Value;

    /**
     * Always keeps track of its own parent
     */
    TreeNode<DataType>* Parent = nullptr;

    /**
     * Next leaf (no meaning if this is not a leaf)
     */
    TreeNode<DataType>* Next = nullptr;
    /**
     * Previous leaf (no meaning if this is not a leaf)
     */
    TreeNode<DataType>* Previous = nullptr;

    /**
     * Init a new node with two children
     * @param small
     * @param big
     * @param key will be used to route to small or big,
     * should be lower or equal to smallest leaf on big and bigger than biggest leaf in small
     * @param parent this node's parent
     */
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> big,
             DataType key,
             TreeNode<DataType>* parent = nullptr);

    /**
     * Init a new node with three children
     * @param small
     * @param middle
     * @param big
     * @param key1 smallest key
     * @param key2 biggest key
     * @param parent this node's parent
     */
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middle,
             SharedPointer<TreeNode<DataType>> big,
             DataType key1,
             DataType key2,
             TreeNode<DataType>* parent = nullptr);

    /**
     * Init a new node with four children (should only be temporary)
     * @param small
     * @param middleOne
     * @param middleTwo
     * @param big
     * @param key1 smallest key
     * @param key2 middle key
     * @param key3 biggest key
     * @param parent this node's parent
     */
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middleOne,
             SharedPointer<TreeNode<DataType>> middleTwo,
             SharedPointer<TreeNode<DataType>> big,
             DataType key1,
             DataType key2,
             DataType key3,
             TreeNode<DataType>* parent = nullptr);
    TreeNode(DataType value, TreeNode<DataType>* parent = nullptr) : Value(value), Sons(0), Parent(parent) {
    }

    /**
     * Tries to find the shared pointer version of the parent's pointer, can fail
     * @return if succeeded returns a non-empty shared pointer of the parent, empty shared pointer otherwise.
     */
    SharedPointer<TreeNode<DataType>> getSharedParent();
    /**
     * Insert key in the right place in the node's indices, with first half before it (overriding corresponding child)
     * and second half after.
     * @param firstHalf child that overrides the previous child
     * @param secondHalf the second child
     * @param key new key to route between the two
     */
    void swap(SharedPointer<TreeNode<DataType>> firstHalf,
               SharedPointer<TreeNode<DataType>> secondHalf,
               DataType key);
    /**
     * Remove the son with the corresponding value (works on non-leaves as well)
     * @param value the son's value
     */
    void removeSon(DataType value);
    /**
     * Insert the node as a new son
     * @param new_node the new son to insert
     */
    void insertValue(SharedPointer<TreeNode<DataType>> new_node);
    /**
     * Check if the node is a leaf (no sons)
     * @return is a leaf
     */
    bool isLeaf() const;
    /**
     * Borrow children from a relative node
     * @param id this node's index in its parent (which child number is it)
     * @param other the relative from which to borrow children
     */
    void borrow(int id, int other);
    /**
     * Combine with a relative, fixing the parent to point to the combined node
     * @param id this node's index in its parent (which child number is it)
     * @param other the relative to combine with
     */
    void combine(int id, int other);
    /**
     * Print this node (using str() on DataType)
     */
    void printNode();
};

template<typename DataType>
SharedPointer<TreeNode<DataType>> TreeNode<DataType>::getSharedParent() {
    auto p = this->Parent;
    if (p->Parent == nullptr) return SharedPointer<TreeNode<DataType>>();
    if (p->Parent->Children[0] == p) {
        return p->Parent->Children[0];
    }
    else if (p->Parent->Children[1] == p) {
        return p->Parent->Children[1];
    }
    return p->Parent->Children[2];
}

template<typename DataType>
void TreeNode<DataType>::swap(SharedPointer<TreeNode<DataType>> firstHalf, SharedPointer<TreeNode<DataType>> secondHalf,
                              DataType key) {
    for (int i = 0; i < Sons-1; i++) {
        // if key should insert between i-1 & i
        if (key < Indices[i]) {
            DataType tmpPrev = key;
            Children[i] = firstHalf;
            SharedPointer<TreeNode<DataType>> childTmpPrev = secondHalf;
            for (; i < Sons-1; i++) {
                DataType tmp = Indices[i];
                Indices[i] = tmpPrev;
                SharedPointer<TreeNode<DataType>> childTmp = Children[i+1];
                Children[i+1] = childTmpPrev;
                childTmpPrev = childTmp;
                tmpPrev = tmp;
            }
            Indices[i] = tmpPrev;
            Children[i+1] = childTmpPrev;
            if (i == 0) {
                Value = firstHalf->Value;
            }
        }
        // If reached end of indices and key still bigger, insert in the end
        if (i == Sons-2 && Indices[i] < key) {
            Indices[i+1] = key;
            Children[i+1] = firstHalf;
            Children[i+2] = secondHalf;
        }
    }
    Sons++;
    firstHalf->Parent = this;
    secondHalf->Parent = this;
}

template<typename DataType>
void TreeNode<DataType>::removeSon(DataType value) {
    if (this->Sons == 3) {
        if (this->Children[0]->Value == value) {
            this->Children[1]->Previous = this->Children[0]->Previous;
            if(this->Children[0]->Previous != nullptr) this->Children[0]->Previous->Next = this->Children[1].rawPointer();

            this->Indices[0] = this->Indices[1]; // update node Indices
            this->Children[0] = this->Children[1]; // update node children
            this->Children[1] = this->Children[2];
            this->Value = this->Children[0]->Value; // update node value
        }
        else if (this->Children[1]->Value == value) {
            this->Children[0]->Next = this->Children[1]->Next;
            this->Children[2]->Previous = this->Children[1]->Previous;

            this->Children[1] = this->Children[2];
            this->Indices[0] = this->Indices[1];
        }
        else{
            this->Children[1]->Next = this->Children[2]->Next;
            if(this->Children[2]->Next != nullptr) this->Children[2]->Next->Previous = this->Children[1].rawPointer();
        }
    }
    else if(this->Sons == 2){
        if (this->Children[0]->Value == value) {
            this->Children[1]->Previous = this->Children[0]->Previous;
            if(this->Children[0]->Previous != nullptr) this->Children[0]->Previous->Next = this->Children[1].rawPointer();

            this->Indices[0] = this->Indices[1];
            this->Children[0] = this->Children[1];
            this->Value = this->Children[0]->Value; // update node value
        }
        else{
            this->Children[0]->Next = this->Children[1]->Next;
            if(this->Children[1]->Next != nullptr) this->Children[1]->Next->Previous = this->Children[0].rawPointer();
        }
    }
    this->Sons--;
}

template<typename DataType>
void TreeNode<DataType>::insertValue(SharedPointer<TreeNode<DataType>> new_node) {
    DataType value = new_node->Value;

    int i = 0;
    bool changed = false;
    for (; i < Sons-1; i++) {
        if (value < Indices[i]) {
            changed = true;
            DataType keyPushNext = Indices[i];
            SharedPointer<TreeNode<DataType>> childPushNext;
            if (value < Children[i]->Value) {
                Value = value;
                new_node->Previous = Children[i]->Previous;
                if (new_node->Previous != nullptr) new_node->Previous->Next = new_node.rawPointer();

                childPushNext = Children[i];
                Indices[i] = Children[i]->Value;
                Children[i] = new_node;

            } else {
                new_node->Next = Children[i]->Next;
                if (new_node->Next != nullptr) new_node->Next->Previous = new_node.rawPointer();

                DataType keyPushNext = Indices[i];
                Indices[i] = value;
                childPushNext = new_node;
            }

            Children[i]->Next = childPushNext.rawPointer();
            childPushNext->Previous = Children[i].rawPointer();

            for (; i < Sons - 1; i++) {
                DataType tmpKey = Indices[i + 1];
                SharedPointer<TreeNode<DataType>> tmpChild = Children[i+1];

                Indices[i + 1] = keyPushNext;
                Children[i + 1] = childPushNext;

                childPushNext = tmpChild;
                if(i+1 < Sons-1) keyPushNext = tmpKey;
            }
            if(i+1 < Sons-1) Indices[i + 1] = keyPushNext;
            Children[i + 1] = childPushNext;
            break;
        }
    }
    SharedPointer<TreeNode<DataType>> prev;
    if (!changed) {
        if (value < Children[i]->Value) {
            Indices[i] = Children[i]->Value;
            Children[i+1] = Children[i];
            Children[i] = new_node;
            prev = Children[i-1];
        }
        else {
            Indices[i] = value;
            Children[i+1]  = new_node;
            prev = Children[i];
        }

        auto tmpNext = prev->Next;
        prev->Next = new_node.rawPointer();
        new_node->Next = tmpNext;
        new_node->Previous = prev.rawPointer();
        if (tmpNext != nullptr) tmpNext->Previous = new_node.rawPointer();
    }
    Sons++;
    new_node->Parent = this;
}

template<typename DataType>
bool TreeNode<DataType>::isLeaf() const {
    return Sons == 0;
}

template<typename DataType>
void TreeNode<DataType>::borrow(int id, int other) {
    if (other > id) { // borrowing from right hand side
        // fixing indicators
        this->Indices[0] = this->Parent->Indices[other - 1];
        this->Parent->Indices[other - 1] = this->Parent->Children[other]->Indices[0];

        // transferring the first child of other node
        this->Children[1] = this->Parent->Children[other]->Children[0];
        this->Children[1]->Parent = this;

        // fixing the other node
        this->Parent->Children[other]->Sons = 2;
        this->Parent->Children[other]->Indices[0] = this->Parent->Children[other]->Indices[1];
        this->Parent->Children[other]->Children[0] = this->Parent->Children[other]->Children[1];
        this->Parent->Children[other]->Children[1] = this->Parent->Children[other]->Children[2];
        this->Parent->Children[other]->Value = this->Parent->Children[other]->Children[0]->Value;
    } else { // borrowing from left hand side
        // fixing indicators
        this->Indices[0] = this->Parent->Indices[other];
        this->Parent->Indices[other] = this->Parent->Children[other]->Indices[1];

        // transferring the last child of other node
        this->Children[1] = this->Children[0];
        this->Children[0] = this->Parent->Children[other]->Children[2];
        this->Children[0]->Parent = this;
        this->Value = this->Children[0]->Value;
        // fixing the other node
        this->Parent->Children[other]->Sons = 2;
    }
    this->Sons = 2;
}

template<typename DataType>
void TreeNode<DataType>::combine(int id, int other) {
    if (other > id){ // combining with right hand side
        // transferring the children other node
        this->Children[1] = this->Parent->Children[other]->Children[0];
        this->Children[2] = this->Parent->Children[other]->Children[1];
        this->Children[1]->Parent = this;
        this->Children[2]->Parent = this;

        // fixing indicators
        this->Indices[0] = this->Children[1]->Value;
        this->Indices[1] = this->Children[2]->Value;
    }
    else{ // combining with left hand side
        // transferring the children other node
        this->Children[2] = this->Children[0];
        this->Children[0] = this->Parent->Children[other]->Children[0];
        this->Children[1] = this->Parent->Children[other]->Children[1];
        this->Children[0]->Parent = this;
        this->Children[1]->Parent = this;

        // fixing indicators
        this->Indices[0] = this->Children[1]->Value;
        this->Indices[1] = this->Children[2]->Value;

        this->Parent->Indices[other] = this->Children[0]->Value;

        this->Value = this->Children[0]->Value;
    }
    Sons = 3;
    //delete other node
    this->Parent->removeSon(this->Parent->Children[other]->Value);
}

template<typename DataType>
void TreeNode<DataType>::printNode() {
    cout << "Sons: " << Sons << ", ";
    cout << "Indices: [";
    for (int i = 0; i < Sons-1; i++) {
        cout << Indices[i].str();
        if (i != Sons-2) {
            cout << ",";
        }
    }
    cout << "], Children (Values): [";
    for (int i = 0; i < Sons; i++) {
        cout << Children[i]->Value.str();
        if (i != Sons-1) {
            cout << ",";
        }
    }
    cout << "], Value: " << Value.str() << "." << endl;

}

template<typename DataType>
TreeNode<DataType>::TreeNode(SharedPointer<TreeNode<DataType>> small, SharedPointer<TreeNode<DataType>> big,
                             DataType key, TreeNode<DataType> *parent) : Sons(2), Parent(parent) {
    Indices[0] = key;
    Children[0] = small;
    Children[1] = big;
    Value = small->Value;
    small->Parent = this;
    big->Parent = this;
}

template<typename DataType>
TreeNode<DataType>::TreeNode(SharedPointer<TreeNode<DataType>> small, SharedPointer<TreeNode<DataType>> middle,
                             SharedPointer<TreeNode<DataType>> big, DataType key1, DataType key2,
                             TreeNode<DataType> *parent) : Sons(3), Parent(parent) {
    Indices[0] = key1;
    Indices[1] = key2;
    Children[0] = small;
    Children[1] = middle;
    Children[2] = big;
    Value = small->Value;
    small->Parent = this;
    middle->Parent = this;
    big->Parent = this;
}

template<typename DataType>
TreeNode<DataType>::TreeNode(SharedPointer<TreeNode<DataType>> small, SharedPointer<TreeNode<DataType>> middleOne,
                             SharedPointer<TreeNode<DataType>> middleTwo, SharedPointer<TreeNode<DataType>> big,
                             DataType key1, DataType key2, DataType key3, TreeNode<DataType> *parent) : Sons(4), Parent(parent) {
    Indices[0] = key1;
    Indices[1] = key2;
    Indices[2] = key3;
    Children[0] = small;
    Children[1] = middleOne;
    Children[2] = middleTwo;
    Children[3] = big;
    Value = small->Value;
    small->Parent = this;
    middleOne->Parent = this;
    middleTwo->Parent = this;
    big->Parent = this;
}


#endif //DS_EX1_TREE_NODE_H
