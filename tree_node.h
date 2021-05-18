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

template <typename DataType>
struct TreeNode {
    Vector<DataType> Indices=Vector<DataType>(3);
    int Sons;

    DataType Value;

    TreeNode<DataType>* Parent = nullptr;

    Vector<SharedPointer<TreeNode<DataType>>> Children = Vector<SharedPointer<TreeNode<DataType>>>(4);

    TreeNode<DataType>* Next = nullptr;

    TreeNode<DataType>* Previous = nullptr;

    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> big,
             DataType key,
             TreeNode<DataType>* parent = nullptr) : Sons(2), Parent(parent) {
        Indices[0] = key;
        Children[0] = small;
        Children[1] = big;
        Value = small->Value;
    }

    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middle,
             SharedPointer<TreeNode<DataType>> big,
             DataType key1,
             DataType key2,
             TreeNode<DataType>* parent = nullptr) : Sons(3), Parent(parent) {
        Indices[0] = key1;
        Indices[1] = key2;
        Children[0] = small;
        Children[1] = middle;
        Children[2] = big;
        Value = small->Value;
    }

    TreeNode(SharedPointer<TreeNode<DataType>> small,
             SharedPointer<TreeNode<DataType>> middleOne,
             SharedPointer<TreeNode<DataType>> middleTwo,
             SharedPointer<TreeNode<DataType>> big,
             DataType key1,
             DataType key2,
             DataType key3,
             TreeNode<DataType>* parent = nullptr) : Sons(4), Parent(parent) {
        Indices[0] = key1;
        Indices[1] = key2;
        Indices[2] = key3;
        Children[0] = small;
        Children[1] = middleOne;
        Children[2] = middleTwo;
        Children[3] = big;
        Value = small->Value;
    }
    TreeNode(DataType value, TreeNode<DataType>* parent = nullptr) : Value(value), Sons(0), Parent(parent) {
    }

    SharedPointer<TreeNode<DataType>> getSharedParent() {
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

    void swap(SharedPointer<TreeNode<DataType>> firstHalf,
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

    void removeSon(DataType value) {
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

    void insertValue(SharedPointer<TreeNode<DataType>> new_node) {
        DataType value = new_node->Value;

        int i = 0;
        bool changed = false;
        for (; i < Sons-1; i++) {
            if (value < Indices[i]) {
                if (i == 0) {
                    Value = value;
                }
                changed = true;
                DataType keyPushNext = Indices[i];
                SharedPointer<TreeNode<DataType>> childPushNext;
                if (value < Children[i]->Value) {
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
        if (!changed) {
            if (value < Children[i]->Value) {
                Indices[i] = Children[i]->Value;
                Children[i+1] = Children[i];
                Children[i] = new_node;
            }
            else {
                Indices[i] = value;
                Children[i+1]  = new_node;
            }

            Children[i]->Next = Children[i+1].rawPointer();
            Children[i+1]->Previous = Children[i].rawPointer();

            if(this->Parent != nullptr){

            }

        }
        Sons++;
        new_node->Parent = this;
    }

    bool isLeaf() const {
        return Sons == 0;
    }

    void borrow(int id, int other) {
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
        } else { // borrowing from left hand side
            // fixing indicators
            this->Indices[0] = this->Parent->Indices[other];
            this->Parent->Indices[other] = this->Parent->Children[other]->Indices[1];

            // transferring the last child of other node
            this->Children[1] = this->Children[0];
            this->Children[0] = this->Parent->Children[other]->Children[2];
            this->Children[0]->Parent = this;

            // fixing the other node
            this->Parent->Children[other]->Sons = 2;
        }
        this->Sons = 2;
    }

    void combine(int id, int other){
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

            this->Value = this->Children[0]->Value;
        }
        Sons = 3;
        //delete other node
        this->Parent->removeSon(this->Parent->Children[other]->Value);
    }

    void printNode() {
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
};


#endif //DS_EX1_TREE_NODE_H
