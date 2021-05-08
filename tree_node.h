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

    SharedPointer<TreeNode> Parent = SharedPointer<TreeNode<DataType>>();

    Vector<SharedPointer<TreeNode<DataType>>> Children = Vector<SharedPointer<TreeNode<DataType>>>(4);

    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> big,
             DataType key,
             SharedPointer<TreeNode<DataType>> parent) : Sons(2), Parent(parent) {
        Indices[0] = key;
        Children[0] = small;
        Children[1] = big;
    }
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middle,
             SharedPointer<TreeNode<DataType>> big,
             DataType key1,
             DataType key2,
             SharedPointer<TreeNode<DataType>> parent) : Sons(3), Parent(parent) {
        Indices[0] = key1;
        Indices[1] = key2;
        Children[0] = small;
        Children[1] = middle;
        Children[2] = big;
    }
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middleOne,
             SharedPointer<TreeNode<DataType>> middleTwo,
             SharedPointer<TreeNode<DataType>> big,
             DataType key1,
             DataType key2,
             DataType key3,
             SharedPointer<TreeNode<DataType>> parent) : Sons(4), Parent(parent) {
        Indices[0] = key1;
        Indices[1] = key2;
        Indices[2] = key3;
        Children[0] = small;
        Children[1] = middleOne;
        Children[2] = middleTwo;
        Children[3] = big;
    }
    TreeNode(DataType value) : Value(value), Sons(0) {
    }

    void Swap(SharedPointer<TreeNode<DataType>> firstHalf,
               SharedPointer<TreeNode<DataType>> secondHalf,
               DataType key) {
        firstHalf->Parent = this;
        secondHalf->Parent = this;
        Vector<SharedPointer<TreeNode<DataType>>> tmpVec;
        for (int i = 0; i < Sons; i++) {
            if (key < Indices[i]) {
                DataType tmpPrev = key;
                for (; i < Sons; i++) {
                    DataType tmp = Indices[i];
                    Indices[i] = tmpPrev;
                    tmpPrev = tmp;
                }
                Indices[i+Sons] = tmpPrev;
            }
        }
        Sons++;

    }
};


#endif //DS_EX1_TREE_NODE_H
