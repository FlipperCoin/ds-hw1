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
             SharedPointer<TreeNode<DataType>> parent = SharedPointer<TreeNode<DataType>>()) : Sons(2), Parent(parent) {
        Indices[0] = key;
        Children[0] = small;
        Children[1] = big;
    }
    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middle,
             SharedPointer<TreeNode<DataType>> big,
             DataType key1,
             DataType key2,
             SharedPointer<TreeNode<DataType>> parent = SharedPointer<TreeNode<DataType>>()) : Sons(3), Parent(parent) {
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
             SharedPointer<TreeNode<DataType>> parent = SharedPointer<TreeNode<DataType>>()) : Sons(4), Parent(parent) {
        Indices[0] = key1;
        Indices[1] = key2;
        Indices[2] = key3;
        Children[0] = small;
        Children[1] = middleOne;
        Children[2] = middleTwo;
        Children[3] = big;
    }
    TreeNode(DataType value, SharedPointer<TreeNode<DataType>> parent = SharedPointer<TreeNode<DataType>>()) : Value(value), Sons(0), Parent(parent) {
    }

    void Swap(SharedPointer<TreeNode<DataType>> firstHalf,
               SharedPointer<TreeNode<DataType>> secondHalf,
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
            }
            // If reached end of indices and key still bigger, insert in the end
            if (i == Sons-2 && key > Indices[i]) {
                Indices[i+1] = key;
                Children[i+1] = firstHalf;
                Children[i+2] = secondHalf;
            }
        }
        Sons++;
    }

    void insertValue(SharedPointer<TreeNode<DataType>> new_node) {
        DataType value = new_node.getValue();
        int i = 0;
        for (; i < Sons-1; i++) {
            if (value < Indices[i]) {

                if (value < Children[i]) {
                    DataType keyPushNext = Indices[i];
                    SharedPointer<TreeNode<DataType>> childPushNext = Children[i];
                    Indices[i] = Children[i].getValue();
                    Children[i] = new_node;
                } else {
                    DataType keyPushNext = Indices[i];
                    Indices[i] = value;
                    SharedPointer<TreeNode<DataType>> childPushNext = new_node;
                }
                for (; i < Sons - 1; i++) {
                    DataType tmpKey = Indices[i + 1];
                    SharedPointer<TreeNode<DataType>> tmpChild = Children[i + 1];

                    Indices[i + 1] = keyPushNext;
                    Children[i + 1] = childPushNext;

                    childPushNext = tmpChild;
                    keyPushNext = tmpKey;
                }
                Indices[i + 1] = keyPushNext;
                Children[i + 1] = childPushNext;
                break;
            }
        }
        if (i == Sons - 1) {
            if (value < Children[i]) {
                Indices[i] = Children[i].GetValue();
                Children[i+1] = Children[i];
                Children[i] = new_node;

            }
            else {
                Indices[i] = value;
                Children[i+1]  = new_node;
            }
        }
        Sons++;
    }

};


#endif //DS_EX1_TREE_NODE_H
